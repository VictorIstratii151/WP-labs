#pragma once
#ifndef BALLINFO_H
#define BALLINFO_H
#include <windows.h>

class MovingObject
{
public:
	COLORREF color;
	POINT center;
	POINT delta;
	int idObj;
	int	idHitObj;
	int acceleration;
	int multiplied;
	BOOL squareCheck;

	MovingObject() : color(RGB(0, 0, 0)), idObj(0), idHitObj(0), acceleration(0), multiplied(0), squareCheck(0)
	{
		center.x = 0;
		center.y = 0;
		delta.x = 0;
		delta.y = 0;
	}

	MovingObject(POINT center, POINT delta, COLORREF color, int idObj) : color(color), idObj(idObj), idHitObj(idObj)
	{
		this->center.x = center.x;
		this->center.y = center.y;
		this->delta.x = delta.x;
		this->delta.y = delta.y;
		acceleration = 0;
		multiplied = 0;
		squareCheck = FALSE;
	}

	void paintObject(COLORREF color);
	void collision(RECT rcClient);
	void move(HDC &hdc, RECT rcCLient);
	void alterDirection(MovingObject obj);
};

#endif

