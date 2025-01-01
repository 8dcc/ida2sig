
CC=gcc
CFLAGS=-Wall -Wextra
LDLIBS=

BIN=ida2sig sig2ida

PREFIX=/usr/local
BINDIR=$(PREFIX)/bin

#-------------------------------------------------------------------------------

.PHONY: all clean

all: $(BIN)

clean:
	rm -f $(BIN)

install: $(BIN)
	install -D -m 755 ./ida2sig -t $(BINDIR)
	install -D -m 755 ./sig2ida -t $(BINDIR)

#-------------------------------------------------------------------------------

$(BIN): % : src/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)
