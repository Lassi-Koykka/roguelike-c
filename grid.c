#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_MAX_W 1024
#define GRID_MAX_H 1024

#define max(x, y) x > y ? x : y

Grid* new_grid(int cols, int rows) {
    char *values = calloc(cols * rows, sizeof(char));
    assert(values != NULL);
    char **grid = malloc(rows * sizeof(char*));
    assert(grid != NULL);
    for (int i=0; i<rows; ++i)
    {
        grid[i] = values + i * cols;
    }
    Grid *g = malloc(sizeof(Grid));
    assert(g != NULL);
    g->h = rows;
    g->w = cols;
    g->data = grid;
    return g;
}

Grid* read_grid_from_file(char *filepath) {
    FILE *f = fopen(filepath, "r");
    assert(f != NULL);

    char s[GRID_MAX_W];

    int cols = 0;
    int rows = 0;
    while((fgets(s, GRID_MAX_W, f)) != NULL) {
        cols = max(cols, strlen(s) + 1);
        rows++;
    }
    rewind(f);

    Grid* g = new_grid(cols, rows);

    int i = 0;
    while((fgets(g->data[i], cols, f)) != NULL)
        i++;

    fclose(f);
    return g;
}

void print_grid(FILE *f, Grid* g, int spacing) {
    for(int i = 0; i < g->h; i++) {
        for(int j = 0; j < g->w; j++) {
            fprintf(f, "%c", g->data[i][j]);
            for(int x = 0; x < spacing; x++)
                fprintf(f, " ");
        }
        fprintf(f, "\n");
    }
}

void free_grid(Grid *grid) {
    free(*grid->data);
    free(grid->data);
    free(grid);
}
