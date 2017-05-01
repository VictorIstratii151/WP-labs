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