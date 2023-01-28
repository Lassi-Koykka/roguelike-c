#include <assert.h>
#include <stdio.h>

typedef struct {
    int w;
    int h;
    char **data;
} Grid;

Grid* new_grid(int cols, int rows);

void print_grid(FILE *f, Grid* g, int spacing);

void free_grid(Grid *grid);


Grid* read_grid_from_file(char *filepath);
