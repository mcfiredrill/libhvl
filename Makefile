# Quick Makefile hack for Hively's replayer
# Christopher O'Neill (Deltafire) 11/10/06

play_hvl:	hvl_replay.c hvl_replay.h play_hvl.c types.h
	gcc -g -o play_hvl hvl_replay.c play_hvl.c -lSDL

