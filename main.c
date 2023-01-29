#include <assert.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "camera.h"
#include "drawing.h"

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
        tilesize += GetMouseWheelMove()*4.0f;

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

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("Use mouse wheel to change font size", 20, 20, 10, GRAY);
            BeginMode2D(camera);
                DrawMap(map);
                DrawAscii(playerChar, playerPos, GOLD, curTileColor.bg, 1);
            EndMode2D();

            DrawText(TextFormat("Tilesize size: %02.02f", tilesize), 20, screenHeight - 50, 10, WHITE);


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
