#pragma once

typedef struct _BALLINFO
{
	int width;
	int height;
	int x;
	int y;
	int centerX;
	int centerY;

	int dx;
	int dy;

	int moving_delta;

	struct _BALLINFO initBall(int w, int h, int _x, int _y, int _centerX, int _centerY, int _dx, int _dy, int delta)
	{
		width = w;
		height = h;
		x = _x;
		y = _y;
		centerX = _centerX;
		centerY = _centerY;
		dx = _dx;
		dy = _dy;
		moving_delta = delta;
	}
}BALLINFO;

