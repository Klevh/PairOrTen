#!/bin/makefile

OFILES=io.o main.o jeu.o
EXEC=smallGame

LDFLAGS=-g
CFLAGS=-Wall -Wextra -ansi -pedantic

CC=gcc

CLEAN=*.o *~

all:$(EXEC)

$(EXEC):$(OFILES)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm $(CLEAN)
clear: clean

cleaner:
	rm $(EXEC) $(CLEAN)
