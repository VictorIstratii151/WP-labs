#include "objInfo.h"

void MovingObject::paintObject(COLORREF color)
{
	this->color = color;
}

void MovingObject::move(HDC & hdc, RECT rcClient)
{
	HBRUSH brush = CreateSolidBrush(color);
	SelectObject(hdc, brush);

	collision(rcClient);
	center.x += delta.x + (delta.x / abs(delta.x)) * acceleration;
	center.y += delta.y + (delta.y / abs(delta.y)) * acceleration;

	if (acceleration > 10)
	{
		acceleration = 10;
	}

	if (squareCheck == FALSE)
	{
		Ellipse(hdc, center.x - 25, center.y - 25, center.x + 25, center.y + 25);
	}
	else
	{
		Rectangle(hdc, center.x - 25, center.y - 25, center.x + 25, center.y + 25);
	}

	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	DeleteObject(brush);
}

void MovingObject::collision(RECT rcClient)
{
	if (center.x + 25 > rcClient.right - 1)
	{
		idHitObj = 1001;
		squareCheck = TRUE;
		delta.x = -abs(delta.x);
	}
	if (center.x - 25 < rcClient.left + 1)
	{
		squareCheck = TRUE;
		idHitObj = 1001;
		delta.x = abs(delta.x);
	}
	if (center.y + 25 > rcClient.bottom - 1)
	{
		idHitObj = 1001;
		squareCheck = FALSE;
		acceleration += 1;
		delta.y = -abs(delta.y);

	}
	if (center.y - 25 < rcClient.top + 10)
	{
		acceleration += 1;
		squareCheck = FALSE;
		idHitObj = 1001;
		delta.y = abs(delta.y);
	}
}
