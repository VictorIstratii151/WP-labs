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
		squareCheck = TRUE;
		delta.x = -abs(delta.x);
		idHitObj = 1001;
	}
	if (center.x - 25 < rcClient.left + 1)
	{
		squareCheck = TRUE;
		delta.x = abs(delta.x);
		idHitObj = 1001;
	}
	if (center.y + 25 > rcClient.bottom - 1)
	{
		squareCheck = FALSE;
		acceleration += 1;
		delta.y = -abs(delta.y);
		idHitObj = 1001;

	}
	if (center.y - 25 < rcClient.top + 10)
	{
		acceleration += 1;
		squareCheck = FALSE;
		delta.y = abs(delta.y);
		idHitObj = 1001;
	}
}

void MovingObject::alterDirection(MovingObject obj)
{
	if (obj.delta.x > 0 && obj.delta.y < 0)
	{
		delta.x = abs(delta.x);
		delta.y = abs(delta.y);
	}
	else if (obj.delta.x > 0 && obj.delta.y > 0)
	{
		delta.x = abs(delta.x);
		delta.y = -abs(delta.y);
	}
	else if (obj.delta.x < 0 && obj.delta.x > 0)
	{
		delta.x = -abs(delta.x);
		delta.y = -abs(delta.y);
	}
	else if (obj.delta.x < 0 && obj.delta.y < 0)
	{
		delta.x = -abs(delta.x);
		delta.y = abs(delta.y);
	}
}

void interaction(MovingObject & a, MovingObject &b)
{
	if (!(a.idHitObj == b.idObj && a.idObj == b.idHitObj))
	{
		int R = rand() % 256;
		int G = rand() % 256;
		int B = rand() % 256;
		int R_2 = rand() % 256;
		int G_2 = rand() % 256;
		int B_2 = rand() % 256;

		int distance = sqrt(pow(abs(b.center.x - a.center.x), 2) + pow(abs(b.center.y - a.center.y), 2));
		if (distance <= 45)
		{
			if (a.squareCheck & b.squareCheck || !a.squareCheck & !b.squareCheck)
			{
				a.color = RGB(R, G, B);
				b.color = RGB(R_2, G_2, B_2);
				if (a.multiplied == 0)
					a.multiplied = 1;
				if (b.multiplied == 0)
					b.multiplied = 1;
			}

			a.idHitObj = b.idObj;
			b.idHitObj = a.idObj;
			a.delta.x = -a.delta.x;
			a.delta.y = -a.delta.y;

			b.delta.x = -b.delta.x;
			b.delta.y = -b.delta.y;
		}
	}
}