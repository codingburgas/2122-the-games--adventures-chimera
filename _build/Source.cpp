#include "raylib.h"

int main(void)
{
    const int screenWidth = 960;
    const int screenHeight = 894;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    Texture2D mickey = LoadTexture("../resources/mickey.png");
    float frameWidth = (float)(mickey.width / 3);

    Texture2D map = LoadTexture("../resources/map.png");
    float mapFrameWidth = (float)(map.width / 12);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTextureRec(map, Rectangle{ 0, 0, mapFrameWidth, (float)map.height }, { 0, 15 }, WHITE);
        DrawTextureRec(mickey, Rectangle{ 0, 0, frameWidth, (float)mickey.height }, { 20, 628 }, WHITE);

        EndDrawing();
    }
    UnloadTexture(mickey);
    UnloadTexture(map);

    CloseWindow();

    return 0;
}