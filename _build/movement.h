#pragma once

#include "raylib.h"

void mickeyWalking(float& frameWidth, float& x, float& time, int& frame, int& maxFrames, Rectangle& frameChange);
void mickeyJumping(float& y, bool& jump, int& jumpTimer);
void backgroundMovement(Texture2D &map, float &scrollingBack);