
CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=

BIN=ida2sig.out sig2ida.out

.PHONY: clean all

# -------------------------------------------

all: $(BIN)

clean:
	rm -f $(BIN)

# -------------------------------------------

$(BIN): %.out : src/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
