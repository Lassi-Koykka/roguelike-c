CC = gcc
CFLAGS = -g -std=c99 -Wall -pedantic
LFLAGS = -lraylib -lm
FILES = main.c camera.c grid.c drawing.c

all: roguelike

roguelike: $(FILES)
	$(CC) $(CFLAGS) -o roguelike $(FILES) $(LFLAGS)

