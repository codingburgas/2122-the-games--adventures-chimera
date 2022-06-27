#include "movement.h"

//Displays Mickey Walking Animation
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

// Walking Mechanic
void mickeyWalking(float& frameWidth, float& x, float& time, int& frame, int& maxFrames, Rectangle& frameChange)
{
	//Either A or D pressed walking animation displays
	if (IsKeyDown(KEY_D))
	{
		animation(time, frame, maxFrames, frameChange, frameWidth);
	}
	if (IsKeyDown(KEY_A))
	{
		animation(time, frame, maxFrames, frameChange, frameWidth);
	}
}

// Jumping Mechanic
void mickeyJumping(float& y, bool& jump, int& jumpTimer)
{
	if (IsKeyPressed(KEY_W))
	{
		jump = 1;
	}

	//Triggers Jumping When W Is Pressed
	if (jump)
	{
		jumpTimer += 1;
		if (jumpTimer < 45)
		{
			y -= 5.5;
		}
		else
		{
			y += 5.5;
		}
	}

	// Goes Intial Position
	if (jumpTimer >= 90)
	{
		jumpTimer = 0;
		jump = 0;
		y = 628;
	}
}

// Background Movement Mechanic
void backgroundMovement(Texture2D &map, float &scrollingBack)
{
	//Moves The Background And Prevents Mickey From Going To Far To The Right
	if (IsKeyDown(KEY_D) && (scrollingBack >= -10570.0f && scrollingBack <= 20.0f))
	{
		scrollingBack -= 10.0f;
		if (scrollingBack <= -map.width * 2)
		{
			scrollingBack = 0;
		}
	}

	////Moves The Background And Prevents Mickey From Going To Far To The Left
	if (IsKeyDown(KEY_A) && (scrollingBack <= 10.0f && scrollingBack >= -10570.0f))
	{
		scrollingBack += 10.0f;
		if (scrollingBack <= -map.width * 2)
		{
			scrollingBack = 0;
		}
	}
}