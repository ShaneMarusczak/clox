IDIR:=include
CC:=cc
CFLAGS:=-I$(IDIR) -Wall -pipe -O2
BIN:=bin

SRC:=src
ODIR:=$(SRC)/obj

# strips directory from found C files in src directory and returns list
# "foo.c bar.c baz.c" from "$(SRC)/foo.c $(SRC)/bar.c $(SRC)/baz.c"
CFILES:=$(notdir $(wildcard $(SRC)/*.c))

# builds object file paths from C file names and returns list
# "$(ODIR)/foo.o $(ODIR)/bar.o $(ODIR)/baz.o" from "foo.c bar.c baz.c"
OBJS:=$(patsubst %.c, $(ODIR)/%.o, $(CFILES))

# builds list of all header files in $(IDIR)
# "$(IDIR)/foo.h $(IDIR)/bar.h $(IDIR)/baz.h;
DEPS:=$(wildcard $(IDIR)/*.h)

# rule for building the found object files with the corresponding C file dep and all headers
$(ODIR)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clox: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	mv clox $(BIN)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BIN)/*
