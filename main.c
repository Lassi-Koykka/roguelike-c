#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "camera.h"
#include "drawing.h"

#define MAX_TILESIZE 128


#define UNKNOWN 0
#define NOT_VISIBLE 1
#define VISIBLE 2

void LoadAssets() {
    LoadFonts();
    SetupTileColors();
}

int IsWall(Grid* g, Vector2 pos) {
    if(pos.x < 0 || pos.y < 0 || pos.x > g->w - 1 || pos.y > g->h - 1) 
        return true;
    char c = g->data[(int)pos.y][(int)pos.x];
    return c == '#' || c == '^';
}

void Fov(Grid* g, Grid *mask, Vector2 pos) {
    for(int row = 0; row < g->h; row++) {
        for(int col = 0; col < g->w; col++) {
            if(abs((int)pos.x - col) > 1 || abs((int)pos.y - row) > 1) {
                if(mask->data[row][col] == 2)
                  mask->data[row][col] = 1;
                continue;
            }
            mask->data[row][col] = 2;
        }
    }
}

int main1() {
    Grid *map = ReadGridFromFile("map.txt");
    PrintGrid(stdout, map, 1);
    return 0;
}


int main() {

    // Initialization
    //--------------------------------------------------------------------------------------

    extern int tilesize;
    Grid* map = ReadGridFromFile("map2.txt");
    Grid* sightmask = NewGrid(map->w, map->h);
    char playerChar[2] = "@";
    Vector2 playerPos = {4, 4};
    // Vector2 playerPos = GridFind(map, '@');
    // map->data[(int)playerPos.y][(int)playerPos.x] = '~';

    int screenWidth = tilesize * 16;
    int screenHeight = tilesize * 8;
    InitWindow(screenWidth, screenHeight, "Roguelike demo");

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)
    LoadAssets();

    Camera2D camera = InitCamera(playerPos, screenWidth, screenHeight);

    double lastMoveTime = GetTime();

    // 60 FPS
    SetTargetFPS(60); 

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // float deltaTime = GetFrameTime();
        float scrollDelta = GetMouseWheelMove()*4.0f;
        float newSize = tilesize + scrollDelta;
        if(newSize > 0 && newSize < MAX_TILESIZE)
            tilesize = newSize;

        double time = GetTime();
        Vector2 prevPos = (Vector2){playerPos.x, playerPos.y};
        int moveReady = time - lastMoveTime > MOVE_COOLDOWN;
        if ((moveReady && IsKeyDown(KEY_LEFT)) || IsKeyPressed(KEY_LEFT)) playerPos.x -= 1;
        if ((moveReady && IsKeyDown(KEY_UP)) || IsKeyPressed(KEY_UP)) playerPos.y -= 1;
        if ((moveReady && IsKeyDown(KEY_RIGHT)) || IsKeyPressed(KEY_RIGHT)) playerPos.x += 1;
        if ((moveReady && IsKeyDown(KEY_DOWN)) || IsKeyPressed(KEY_DOWN)) playerPos.y += 1;

        if(IsWall(map, playerPos)) {
            playerPos.x = prevPos.x;
            playerPos.y = prevPos.y;
        }

        if(prevPos.x != playerPos.x || prevPos.y != playerPos.y)
            lastMoveTime = time;

        TileColor curTileColor =  GetTileColor(map->data[(int)playerPos.y][(int)playerPos.x]);

        Vector2 camPos = GridPosToAbs(playerPos, tilesize);
        camPos.x += tilesize / 2.0f;
        camPos.y += tilesize / 2.0f;
        UpdateCameraCenter(&camera, camPos, screenWidth, screenHeight);

        //LOS
        Fov(map, sightmask, playerPos);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode2D(camera);
                DrawMap(map, sightmask);
                DrawAscii(playerChar, playerPos, GOLD, curTileColor.bg, 1);
            EndMode2D();
            DrawText("Use mouse wheel to zoom", 20, 20, 10, GRAY);
            DrawText(TextFormat("Tilesize size: %d", tilesize), 20, screenHeight - 50, 10, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    FreeGrid(map);
    UnloadFonts();

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;}
