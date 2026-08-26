#pragma once

struct FrameContext
{
	double dt = 0.0;

	int width = 0;
	int height = 0;

	bool rotate = 0;
	int  rotateY = 0;

	int moveX = 0;
	int moveY = 0;
	int moveZ = 0;

	double zoom = 0.0;

	bool toggleTexture = false;
};
