
CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=

BIN=ida2sig sig2ida

.PHONY: clean all

# -------------------------------------------

all: $(BIN)

clean:
	rm -f $(BIN)

# -------------------------------------------

$(BIN): % : src/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
