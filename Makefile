CC = gcc
CFLAGS = -g -std=c99 -Wall -pedantic
LFLAGS = -lraylib -lm

all: roguelike

roguelike: main.c grid.c
	$(CC) $(CFLAGS) -o roguelike main.c grid.c $(LFLAGS)

