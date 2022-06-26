#include "movement.h"

void animation(float& time, int& frame, int& maxFrames, Rectangle& frameChange, float& frameWidth)
{
	time += GetFrameTime();
	if (time >= 0.2f)
	{
		time = 0.0f;
		frame += 1;
	}
	frame = frame % maxFrames;
	frameChange.x = frameWidth * frame;
}

void mickeyWalking(float &frameWidth, float &x, float &time, int &frame, int &maxFrames, Rectangle &frameChange)
{

	if (IsKeyDown(KEY_D))
	{
		x += GetFrameTime() * 250;
		animation(time, frame, maxFrames, frameChange, frameWidth);
	}
	if (IsKeyDown(KEY_A))
	{
		x -= GetFrameTime() * 250;
		animation(time, frame, maxFrames, frameChange, frameWidth);
	}
}

void mickeyJumping(float& y, bool& jump, int& jumpTimer)
{
	if (IsKeyPressed(KEY_W))
	{
		jump = 1;
	}
	if (jump)
	{
		jumpTimer += 1;
		if (jumpTimer < 90)
		{
			y -= 2;
		}
		else
		{
			y += 2;
		}
	}
	if (jumpTimer >= 180)
	{
		jumpTimer = 0;
		jump = 0;
		y = 628;
	}
}