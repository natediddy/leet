#
# Makefile for leeter
# Nathan Forbes
#

CC = gcc
CFLAGS = -O2 -Wall -ansi -march=native -mtune=native
TARGET = leet

SOURCE = leet.c
OBJECT = leet.o

prefix = /usr/local/bin

all: $(TARGET)

$(TARGET): $(OBJECT)
		$(CC) $(CFLAGS) $(OBJECT) -o $(TARGET)

$(OBJECT): $(SOURCE)
		$(CC) $(CFLAGS) -c $(SOURCE)

clean:
		rm -f $(OBJECT)

distclean:
		rm -f $(OBJECT) $(TARGET)

install: $(TARGET)
		install $(TARGET) $(prefix)/$(TARGET)

uninstall:
		rm -f $(prefix)/$(TARGET)

.PHONY: clean distclean install uninstall
