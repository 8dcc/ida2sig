
CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=

BIN=ida2sig sig2ida
INSTALL_DIR=/usr/local/bin

.PHONY: clean all

#-------------------------------------------------------------------------------

all: $(BIN)

clean:
	rm -f $(BIN)

install: $(BIN)
	mkdir -p $(INSTALL_DIR)
	install -m 755 ./ida2sig $(INSTALL_DIR)/ida2sig
	install -m 755 ./sig2ida $(INSTALL_DIR)/sig2ida

#-------------------------------------------------------------------------------

$(BIN): % : src/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
