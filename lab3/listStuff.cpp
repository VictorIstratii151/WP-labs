#include "listStuff.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>

ListItem initListItem(int width, int height)
{
	srand(time(NULL));
	
	int xStart = rand() % width + 1;
	int yStart = rand() % height + 1;
	int xEnd = rand() % width + 1;
	int yEnd = rand() % height + 1;

	ListItem item;

	item.properties.width = rand() % 20 + 1;
	item.properties.colorA = rand() % 255 + 1;
	item.properties.colorB = rand() % 255 + 1;
	item.properties.colorC = rand() % 255 + 1;

	item.xStart = xStart;
	item.xEnd = xEnd;
	item.yStart = yStart;
	item.yEnd = yEnd;

	//item.color = RGB(item.properties.colorA, item.properties.colorB, item.properties.colorC);
	//item.pen = CreatePen(PS_SOLID, item.properties.width, item.color);

	return item;
}
