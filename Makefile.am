#SUBDIRS = src

AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libhvl.la
libhvl_la_SOURCES = hvl/hvl_replay.c

libhvl_la_LDFLAGS = -version-info $(HVL_SO_VERSION)

hvl_includedir = $(includedir)
nobase_hvl_include_HEADERS = hvl/hvl_replay.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = hvl.pc

#example player
noinst_PROGRAMS = example/play_hvl

example_play_hvl_SOURCES = example/play_hvl.c
example_play_hvl_LDADD = hvl/hvl_replay.lo
