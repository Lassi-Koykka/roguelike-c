#include <assert.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

#include "grid.h"

static float tilesize = 96;
static Font font;

void draw_ascii(char* symbol, Vector2 pos, Color fg, Color bg) {
    pos.x *= tilesize;
    pos.y *= tilesize;
    Vector2 size = (Vector2){tilesize, tilesize};
    DrawRectangleV(pos, size, bg);
    DrawTextEx(font, symbol, pos, tilesize, 0, fg);
}

void draw_map(Grid *g) {
    for(int i = 0; i < g->h; i++) {
        for(int j = 0; j < g->w; j++) {
            char symbol[2] = {g->data[i][j]};
            draw_ascii(symbol, (Vector2){i, j}, WHITE, BLANK);
        }
    }
}

Vector2 grid_find(char c, Grid *g) {
    for(int i = 0; i < g->h; i++) {
        for(int j = 0; j < g->w; j++) {
            if (g->data[i][j] == c) 
                return (Vector2){i, j};
        }
    }
    return (Vector2){0,0};
}

int main() {

    // Initialization
    //--------------------------------------------------------------------------------------

    char playerChar[2] = "@";
    Grid* map = read_grid_from_file("map.txt");

    int screenWidth = tilesize * 18;
    int screenHeight = tilesize * 10;
    InitWindow(screenWidth, screenHeight, "Roguelike demo");

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

    // TTF Font loading with custom generation parameters
    font = LoadFontEx("resources/Monospace.ttf", tilesize, 0, 0);

    tilesize = (float)font.baseSize;
    Vector2 playerPos = { 4, 4 };
    double lastMoveTime = GetTime();

    // Setup texture scaling filter
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    // 60 FPS
    SetTargetFPS(60); 

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // float deltaTime = GetFrameTime();
        // Update
        //----------------------------------------------------------------------------------
        tilesize += GetMouseWheelMove()*4.0f;

        Vector2 textSize = MeasureTextEx(font, playerChar, tilesize, 0);
        double time = GetTime();
        if(time - lastMoveTime > 0.15) {
            Vector2 prevPost = (Vector2){playerPos.x, playerPos.y};
            if (IsKeyDown(KEY_LEFT)) playerPos.x -= 1;
            else if (IsKeyDown(KEY_RIGHT)) playerPos.x += 1;
            else if (IsKeyDown(KEY_UP)) playerPos.y -= 1;
            else if (IsKeyDown(KEY_DOWN)) playerPos.y += 1;
            if(prevPost.x != playerPos.x || prevPost.y != playerPos.y)
                lastMoveTime = time;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("Use mouse wheel to change font size", 20, 20, 10, GRAY);

            draw_map(map);
            draw_ascii(playerChar, playerPos, WHITE, BLACK);

            // TODO: It seems texSize measurement is not accurate due to chars offsets...
            //DrawRectangleLines(fontPosition.x, fontPosition.y, textSize.x, textSize.y, RED);

            DrawText(TextFormat("Font size: %02.02f", tilesize), 20, screenHeight - 50, 10, WHITE);
            DrawText(TextFormat("Text size: [%02.02f, %02.02f]", textSize.x, textSize.y), 20, screenHeight - 30, 10, WHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    free_grid(map);
    UnloadFont(font);           // Font unloading

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;}
