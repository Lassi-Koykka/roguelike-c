CC = gcc
CFLAGS =
LFLAGS = -lraylib -lm

all: roguelike-demo

roguelike-demo: main.c 
	$(CC) $(CFLAGS) -o roguelike-demo main.c $(LFLAGS)

