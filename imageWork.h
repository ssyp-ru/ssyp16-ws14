#pragma once
#include "geometry.h"

typedef struct
{
	unsigned char r, g, b;
} Color;

typedef struct
{
	unsigned char *data;
	int width, height, n;
} Image;


void openImage(Image *im, char dir[]);
void saveImage(Image *im, char dir[]);
void closeImage(Image *im);
Color getColor(Image im, int x, int y);
void setColor(Image *im, int x, int y, Color col);
void printColor(Color *col);
void flipVertically(Image *im);
Image* createImage(int width, int height, int n);
