#pragma once

#include "raylib.h"

// Walking Mechanic
void mickeyWalking(float& frameWidth, float& x, float& time, int& frame, int& maxFrames, Rectangle& frameChange);

// Jumping Mechanic
void mickeyJumping(float& y, bool& jump, int& jumpTimer);

// Background Movement Mechanic
void backgroundMovement(Texture2D &map, float &scrollingBack);