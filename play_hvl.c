
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>

#include <assert.h>
#include <SDL/SDL.h>
#include "types.h"

#include "hvl_replay.h"

#define FREQ 48000
#define HIVELY_LEN FREQ/50
#define OUTPUT_LEN 4096

int16 audiobuffer[2][FREQ / 50];
int16 outputBuffer[FREQ / 25];
struct hvl_tune *tune;
size_t hivelyIndex;
int16 hivelyLeft[HIVELY_LEN], hivelyRight[HIVELY_LEN];

void mix_and_play( struct hvl_tune *ht, uint8 *stream, int length );

BOOL init( void )
{
  uint32 i;
  SDL_AudioSpec wanted;

  if(SDL_Init(SDL_INIT_AUDIO)< 0) {
    printf("Could not initialize SDL: %s\n", SDL_GetError());
    SDL_Quit();
    return FALSE;
  }

  wanted.freq = FREQ; 
  wanted.format = AUDIO_S16SYS; 
  wanted.channels = 2; /* 1 = mono, 2 = stereo */
  //wanted.samples = FREQ / 50;
  wanted.samples = OUTPUT_LEN; // HIVELY_LEN;

  wanted.callback = (void*) mix_and_play;
  wanted.userdata = tune;

  if(SDL_OpenAudio(&wanted, NULL) < 0) {
    printf("Failed to open audio device.\n");
    SDL_Quit();
    return FALSE;
  }

  return TRUE;
}

void mix_and_play( struct hvl_tune *ht, uint8 *stream, int length )
{
  int16 *out;
  //int16 *buf1, *buf2;
  int i;
	size_t streamPos = 0;
	length = length >> 1;

  if(tune) {
		// Mix to 16bit interleaved stereo
		out = (int16*) stream;
		// Flush remains of previous frame
		for(i = hivelyIndex; i < (HIVELY_LEN); i++) {
			out[streamPos++] = hivelyLeft[i];
			out[streamPos++] = hivelyRight[i];
		}

		while(streamPos < length) {
			hvl_DecodeFrame( tune, (int8 *) hivelyLeft, (int8 *) hivelyRight, 2 );
			for(i = 0; i < (HIVELY_LEN) && streamPos < length; i++) {
				out[streamPos++] = hivelyLeft[i];
				out[streamPos++] = hivelyRight[i];
			}
		}
		hivelyIndex = i;
  }
}

int main( int argc, char *argv[] )
{
  int i;
	hivelyIndex = HIVELY_LEN;
  if( argc < 2 )
  {
    printf( "Usage: play_hvl <tune>\n" );
    return 0;
  }

  if( init() )
  {
    hvl_InitReplayer();
    tune = hvl_LoadTune( argv[1], FREQ, 4 );
    if( tune )
    {
      BOOL done;
      uint32 gotsigs;

      hvl_InitSubsong( tune, 0 );

      printf( "Songname: %s\nChannels: %i\n", tune->ht_Name, tune->ht_Channels );
      printf( "Instruments:\n" );
      for( i=1; i <= tune->ht_InstrumentNr; i++ )
        printf( "%02ld: %s\n", i, tune->ht_Instruments[i].ins_Name );
     printf( "\n\nHit Enter to quit..\n" );

      SDL_PauseAudio(0);

      // Uncomment to disable looping:
      /*while(!tune->ht_SongEndReached)
          sleep(1);*/
      getchar();
      SDL_PauseAudio(1);
      hvl_FreeTune( tune );
    }
  }
  SDL_Quit();
  return 0;
}
