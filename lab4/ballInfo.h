#pragma once
#ifndef BALLINFO_H
#define BALLINFO_H
#include <windows.h>

class BallInfo
{
public:
	int width;
	int height;
	POINT center;
	POINT delta;

	BallInfo()
	{
		width = 0;
		height = 0;
		center.x = 0;
		center.y = 0;
		delta.x = 0;
		delta.y = 0;
	}

	BallInfo(int w, int h, int cx, int cy, int dx, int dy) : width(w), height(h)
	{
		center.x = cx;
		center.y = cy;
		delta.x = dx;
		delta.y = dy;
	}

};

#endif

