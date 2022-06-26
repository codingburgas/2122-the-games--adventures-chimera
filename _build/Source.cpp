#include "movement.h"


int main(void)
{
    const int screenWidth = 960;
    const int screenHeight = 894;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    Texture2D mickey = LoadTexture("../resources/mickey.png");
    float frameWidth = (float)(mickey.width / 3);
    float positionMickeyX = 20;
    float positionMickeyY = 628;
    float time = 0.0f;
    int frame = 0;
    int maxFrames = (int)(mickey.width / (int)frameWidth);
    Rectangle frameChange = { (frameWidth * frame), 0, frameWidth, (float)mickey.height };
    bool jump = 0;
    int jumpTimer = 0;

    Texture2D map = LoadTexture("../resources/map.png");
    float mapFrameWidth = (float)(map.width / 12);

    while (!WindowShouldClose())
    {
        mickeyWalking(frameWidth, positionMickeyX, time, frame, maxFrames, frameChange);
        mickeyJumping(positionMickeyY, jump, jumpTimer);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawTextureRec(map, Rectangle{ 0, 0, mapFrameWidth, (float)map.height }, { 0, 15 }, WHITE);
        DrawTextureRec(mickey, frameChange, { positionMickeyX, positionMickeyY }, WHITE);

        EndDrawing();
    }
    UnloadTexture(mickey);
    UnloadTexture(map);

    CloseWindow();

    return 0;
}