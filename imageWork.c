#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_TGA
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "imageWork.h"
#include "geometry.h"

void openImage(Image *im, char *dir)
{
	int x, y, n;
	unsigned char *data = stbi_load(dir, &x, &y, &n, 0);
	im->width = x;
	im->height = y;
	im->n = n;
	im->data = data;
}

void saveImage(Image *im, char dir[])
{
	stbi_write_tga(dir, im->width, im->height, im->n, im->data);
}

void closeImage(Image *im)
{
	free(im->data);
	free(&(im->width));
	free(&(im->height));
	free(&(im->n));
}

Color getColor(Image im, int x, int y)
{
	Color newColor;
	newColor.r = im.data[(((im.width * im.n) * y) + x * im.n) + 0];
	newColor.g = im.data[(((im.width * im.n) * y) + x * im.n) + 1];
	newColor.b = im.data[(((im.width * im.n) * y) + x * im.n) + 2];
	return newColor;
}

void setColor(Image *im, int x, int y, Color col)
{
	im->data[(((im->width * im->n) * y) + x * im->n) + 0] = col.r;
	im->data[(((im->width * im->n) * y) + x * im->n) + 1] = col.g;
	im->data[(((im->width * im->n) * y) + x * im->n) + 2] = col.b;
}

void printColor(Color *col)
{
	printf("%d %d %d\n", col->r, col->g, col->b);
}

void flipVertically(Image *im)
{
	int c = 0;
	for (int i = 0; i < im->height / 2; i++)
	{
		for (int j = 0; j < im->width * im->n; j++)
		{
			c = im->data[(im->width * im->n) * i + j];
			im->data[(im->width * im->n) * i + j] = im->data[(im->width * im->n) * (im->height - 1 - i) + j];
			im->data[(im->width * im->n) * (im->height - 1 - i) + j] = c;
		}
	}
}


Image* createImage(int width, int height, int n)
{
	unsigned char *data = (unsigned char*)malloc(sizeof(char) * width * height * n);
	memset(data, 0, width * height * n);
	Image *im = (Image*)malloc(sizeof(Image));
	im->width = width;
	im->height = height;
	im->n = n;
	im->data = data;
	return im;
}
