#include "movement.h"


int main(void)
{
    const int screenWidth = 960;
    const int screenHeight = 894;

    InitWindow(screenWidth, screenHeight, "Mickey");
    SetTargetFPS(60);

    Texture2D mickey = LoadTexture("../resources/mickey.png");
    float frameWidth = (float)(mickey.width / 3);
    float positionMickeyX = 20;
    float positionMickeyY = 628;
    float time = 0.0f;
    int frame = 0;
    int maxFrames = (int)(mickey.width / (int)frameWidth);
    bool jump = 0;
    int jumpTimer = 0;
    Rectangle frameChange = { (frameWidth * frame), 0, frameWidth, (float)mickey.height };

    Texture2D map = LoadTexture("../resources/map.png");
    float mapFrameWidth = (float)(map.width / 12);
    float scrollingBack = 0.0f;

    while (!WindowShouldClose())
    {
        mickeyWalking(frameWidth, positionMickeyX, time, frame, maxFrames, frameChange);
        mickeyJumping(positionMickeyY, jump, jumpTimer);

        backgroundMovement(map, scrollingBack);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawTextureEx(map, { scrollingBack, 20 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(map, { map.width * 2 + scrollingBack, 20 }, 0.0f, 1.0f, WHITE);

        DrawTextureRec(mickey, frameChange, { positionMickeyX, positionMickeyY }, WHITE);

        EndDrawing();
    }
    UnloadTexture(mickey);
    UnloadTexture(map);

    CloseWindow();

    return 0;
}