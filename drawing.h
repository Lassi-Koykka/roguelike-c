#include <raylib.h>
#include "grid.h"

typedef struct {
    Color fg;
    Color bg;
} TileColor;

void LoadFonts();

void SetupTileColors();

void UnloadFonts();

void UpdateTileSize(int val);

void DrawAscii(char* symbol, Vector2 pos, Color fg, Color bg, int bold);

void DrawMap(Grid *g, Grid *sightmask);

TileColor GetTileColor(char c);
