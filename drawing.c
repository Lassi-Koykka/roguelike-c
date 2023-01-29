#include <raylib.h>
#include "config.h"
#include "drawing.h"

int tilesize = DEFAULT_TILESIZE;

static Font defaultFont, boldFont;

static TileColor tileColors[127] = {0};

int IsBlankTile(char c) {
    TileColor tc = tileColors[(int)c];
    return tc.fg.a == 0 && tc.bg.a == 0;
}

void LoadFonts() {
    defaultFont = LoadFontEx("resources/Monospace.ttf", DEFAULT_TILESIZE * 2, 0, 0);
    boldFont = LoadFontEx("resources/MonospaceBold.ttf", DEFAULT_TILESIZE * 2, 0, 0);
    // Setup texture scaling filter
    SetTextureFilter(defaultFont.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(boldFont.texture, TEXTURE_FILTER_BILINEAR);
}

void SetTileColor(char c, Color fg, Color bg) {
    tileColors[(int)c] = (TileColor){fg,bg};
}

TileColor GetTileColor(char c) {
    return tileColors[(int)c];
}

void SetupTileColors() {
    SetTileColor('#', BLACK, GRAY);
    SetTileColor(' ', BLANK, DARKBROWN);
    SetTileColor('~', WHITE, DARKBLUE);
    SetTileColor('^', BLACK, GRAY);
}


void UnloadFonts() {
    UnloadFont(defaultFont);
    UnloadFont(boldFont);
}

int GetTileSize() {
    return tilesize;
} 
void SetTileSize(int val) {
    tilesize = val;
} 

void DrawAscii(char* symbol, Vector2 pos, Color fg, Color bg, int bold) {
    Font font = bold ? boldFont : defaultFont;
    Vector2 absPos = GridPosToAbs(pos, tilesize);
    // Vector2 size = (Vector2){tilesize, tilesize};
    Rectangle rec = {absPos.x, absPos.y, tilesize, tilesize};
    DrawRectangleRec(rec, bg);
    DrawRectangleLinesEx(rec, 0.5, DARKGRAY);
    Vector2 textSize = MeasureTextEx(font, symbol, tilesize, 0);
    absPos.x += textSize.x / 3.0f;
    DrawTextEx(font, symbol, absPos, tilesize, 0, fg);
}

void DrawTile (char* symbol, Vector2 pos) {
    TileColor colors = GetTileColor(symbol[0]);
    DrawAscii(symbol, pos, colors.fg, colors.bg, 1);
}

void DrawMap(Grid *g) {
    for(int row = 0; row < g->h; row++) {
        for(int col = 0; col < g->w; col++) {
            char c = g->data[row][col];
            if(IsBlankTile(c)) continue;
            char symbol[2] = {c};
            Vector2 pos = {col, row};
            DrawTile(symbol, pos);
        }
    }
}
