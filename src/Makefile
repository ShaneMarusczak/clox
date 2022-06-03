IDIR =../include
CC=cc
CFLAGS=-I$(IDIR) -Wall -pipe -O2

ODIR=obj
LDIR =../lib

LIBS=-lm

SRC=.
SRCS=$(wildcard $(SRC)/*.c)
OBJS:= $(patsubst $(SRC)/%.c,$(ODIR)/%.o,$(SRCS))

_DEPS = $(wildcard $(IDIR)/*.h)
DEPS = $(patsubst %,$(IDIR)/%,$(wildcard $(IDIR)/*.h))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clox: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	mv clox ../

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 