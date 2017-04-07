#pragma once
#include <windows.h>

struct itemProperties{
	int width;
	int colorA;
	int colorB;
	int colorC;
};

typedef struct itemProperties ItemProperties;

struct listItem {
	ItemProperties properties;
	HPEN pen;
	COLORREF color;
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;
};

typedef struct listItem ListItem;

ListItem initListItem();