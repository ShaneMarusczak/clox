IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -Wall -pipe -O2

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = chunk.h common.h memory.h debug.h value.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o chunk.o memory.o debug.o value.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clox: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	mv clox ../

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 