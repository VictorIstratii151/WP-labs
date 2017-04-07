#include "listStuff.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>

ListItem initListItem()
{
	srand(time(NULL));

	ListItem item;

	item.properties.width = rand() % 20 + 1;

	item.properties.colorA = rand() % 255 + 1;
	item.properties.colorB = rand() % 255 + 1;
	item.properties.colorC = rand() % 255 + 1;

	item.color = RGB(item.properties.colorA, item.properties.colorB, item.properties.colorC);
	item.pen = CreatePen(PS_SOLID, item.properties.width, item.color);

	return item;
}
