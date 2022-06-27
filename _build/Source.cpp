#include "movement.h"

int main(void)
{
    const int screenWidth = 960;
    const int screenHeight = 894;

    //Initialize Window
    InitWindow(screenWidth, screenHeight, "Mickey");
    
    SetTargetFPS(60);

    // Load Mickey Texture
    Texture2D mickey = LoadTexture("../resources/mickey.png");
    float frameWidth = (float)(mickey.width / 3);
    // Intial Mickey Positions
    float positionMickeyX = 20;
    float positionMickeyY = 628;
    float time = 0.0f;
    int frame = 0;
    int maxFrames = (int)(mickey.width / (int)frameWidth);
    // Checks If S Key Is Pressed
    bool jump = 0;
    // Time Period For Jumping Anmimatoon
    int jumpTimer = 0;
    // Cycle through animation stages
    Rectangle frameChange = { (frameWidth * frame), 0, frameWidth, (float)mickey.height };

    Texture2D map = LoadTexture("../resources/map.png");
    // Load Background Texture
    float mapFrameWidth = (float)(map.width / 12);
    float scrollingBack = 0.0f;

    while (!WindowShouldClose())
    {
        // Function For Walking Animation
        mickeyWalking(frameWidth, positionMickeyX, time, frame, maxFrames, frameChange);

        // Function For Jumping
        mickeyJumping(positionMickeyY, jump, jumpTimer);

        // Function For Background Movement
        backgroundMovement(map, scrollingBack);
       
        BeginDrawing();

        ClearBackground(BLACK);

        // Display Background
        DrawTextureEx(map, { scrollingBack, 20 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(map, { map.width * 2 + scrollingBack, 20 }, 0.0f, 1.0f, WHITE);

        // Display Mickey
        DrawTextureRec(mickey, frameChange, { positionMickeyX, positionMickeyY }, WHITE);

        EndDrawing();
    }
    // Unload Texture
    UnloadTexture(mickey);
    UnloadTexture(map);

    CloseWindow();

    return 0;
}