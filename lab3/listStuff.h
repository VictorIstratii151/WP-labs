#pragma once
struct itemProperties{
	int width;
	int colorA;
	int colorB;
	int colorC;
};

typedef struct itemProperties ItemProperties;

struct listItem {
	ItemProperties properties;
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;
};

typedef struct listItem ListItem;

ListItem initListItem(int width, int height);