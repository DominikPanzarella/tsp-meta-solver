# Generated automatically from Makefile.in by configure.
#
#   This file is part of CONCORDE
#
#   (c) Copyright 1995--1999 by David Applegate, Robert Bixby,
#   Vasek Chvatal, and William Cook
#
#   Permission is granted for academic research use.  For other uses,
#   contact the authors for licensing options.
#
#   Use at your own risk.  We make no guarantees about the
#   correctness or usefulness of this code.
#


SHELL = /bin/sh
SRCROOT = ../..
BLDROOT = ..
CCINCDIR=$(SRCROOT)/INCLUDE

srcdir = ../../KDTREE
VPATH = ../../KDTREE

CC = clang
CFLAGS = -std=gnu89  -I$(BLDROOT)/INCLUDE -I$(CCINCDIR)
LDFLAGS = -std=gnu89 
LIBFLAGS = -lm 
RANLIB = ranlib

OBJ_SUFFIX = o
o = $(OBJ_SUFFIX)

THISLIB=kdtree.a
LIBSRCS=kdbuild.c kdnear.c   kdspan.c kdtwoopt.c
ALLSRCS=kd_main.c $(LIBSRCS)

LIBS=$(BLDROOT)/UTIL/util.a

all: $(THISLIB)

everything: all kdtree

kdtree: kd_main.$o $(THISLIB) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ kd_main.$o $(THISLIB) $(LIBS) $(LIBFLAGS)

clean:
	-rm -f *.$o $(THISLIB) kdtree

OBJS=$(LIBSRCS:.c=.o)

$(THISLIB): $(OBJS)
	$(AR) $(ARFLAGS) $(THISLIB) $(OBJS)
	$(RANLIB) $(THISLIB)

.PHONY: $(BLDROOT)/concorde.a
$(BLDROOT)/concorde.a: $(OBJS)
	$(AR) $(ARFLAGS) $(BLDROOT)/concorde.a $(OBJS)
	$(RANLIB) $(BLDROOT)/concorde.a

include ../INCLUDE/Makefile.common

# DO NOT DELETE THIS LINE -- make depend depends on it.

I=$(CCINCDIR)
I2=$(BLDROOT)/INCLUDE

kd_main.$o:  kd_main.c  $(I)/machdefs.h $(I2)/config.h  $(I)/util.h     \
        $(I)/kdtree.h   
kdbuild.$o:  kdbuild.c  $(I)/machdefs.h $(I2)/config.h  $(I)/util.h     \
        $(I)/kdtree.h   $(I)/macrorus.h 
kdnear.$o:   kdnear.c   $(I)/machdefs.h $(I2)/config.h  $(I)/kdtree.h   \
        $(I)/util.h     $(I)/macrorus.h 
kdspan.$o:   kdspan.c   $(I)/machdefs.h $(I2)/config.h  $(I)/kdtree.h   \
        $(I)/util.h     $(I)/macrorus.h 
kdtwoopt.$o: kdtwoopt.c $(I)/machdefs.h $(I2)/config.h  $(I)/util.h     \
        $(I)/kdtree.h   $(I)/macrorus.h 
