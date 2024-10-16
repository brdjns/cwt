# SPDX-License-Identifier: MIT

.POSIX:
CC       = cc
CFLAGS   = -g3 -O
LDFLAGS  = -lm
PREFIX   = /usr/local

all: cwt

cwt: cwt.o
	$(CC) -o $@ cwt.o $(LDFLAGS)

cwt.o: cwt.c
	$(CC) $(CFLAGS) -c $<

.PHONY: install
install: cwt
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man1
	install cwt $(DESTDIR)$(PREFIX)/bin
	install -m644 cwt.1 $(DESTDIR)$(PREFIX)/share/man/man1

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/cwt
	rm -f $(DESTDIR)$(PREFIX)/share/man/man1/cwt.1

.PHONY: clean
clean:
	rm -f cwt cwt.o