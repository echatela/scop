#pragma once

struct FrameContext
{
	double dt = 0.0;

	int width = 0;
	int height = 0;

	int rotationX = 0;
	int rotationY = 0;
	int rotationZ = 0;

	double zoom = 0.0;

	bool resetPosition = false;
};
