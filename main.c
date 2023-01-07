#include <stdio.h>
#include <raylib.h>

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - font filters");

    const char msg[50] = "@";

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

    // TTF Font loading with custom generation parameters
    Font font = LoadFontEx("resources/Monospace.ttf", 96, 0, 0);

    float fontSize = (float)font.baseSize;
    Vector2 fontPosition = { 40.0f, screenHeight/2.0f - 80.0f };
    Vector2 textSize = { 0.0f, 0.0f };

    // Setup texture scaling filter
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        fontSize += GetMouseWheelMove()*4.0f;

        textSize = MeasureTextEx(font, msg, fontSize, 0);

        if (IsKeyPressed(KEY_LEFT)) fontPosition.x -= fontSize;
        else if (IsKeyPressed(KEY_RIGHT)) fontPosition.x += fontSize;
        else if (IsKeyPressed(KEY_UP)) fontPosition.y -= fontSize;
        else if (IsKeyPressed(KEY_DOWN)) fontPosition.y += fontSize;

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("Use mouse wheel to change font size", 20, 20, 10, GRAY);

            DrawTextEx(font, msg, fontPosition, fontSize, 0, WHITE);

            // TODO: It seems texSize measurement is not accurate due to chars offsets...
            //DrawRectangleLines(fontPosition.x, fontPosition.y, textSize.x, textSize.y, RED);

            DrawRectangle(0, screenHeight - 80, screenWidth, 80, LIGHTGRAY);
            DrawText(TextFormat("Font size: %02.02f", fontSize), 20, screenHeight - 50, 10, DARKGRAY);
            DrawText(TextFormat("Text size: [%02.02f, %02.02f]", textSize.x, textSize.y), 20, screenHeight - 30, 10, DARKGRAY);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadFont(font);           // Font unloading

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;}
