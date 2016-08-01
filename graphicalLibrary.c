#include <stdio.h>

#include "imageWork.h"
#include "geometry.h"
#include "graphicalLibrary.h"

// g-code to go
// TODO - rewrite function
void drawLine(Image *im, int x1, int y1, int x2, int y2, Color col)
{
    float k, b;
    if ((y2 - y1 != 0)&&(x2 - x1 != 0))
    {
        k = (float)(y2 - y1) / (float)(x2 - x1);
        b = (float)(y1 - k * x1);
        if (x1 < x2)
        {
            for (int i = x1; i <= x2; i++)
            {
                setColor(im, i, k * i + b, col);
            }
        } else {
            for (int i = x2; i <= x1; i++)
            {
                setColor(im, i, k * i + b, col);
            }
        }
        if (y1 < y2)
        {
            for (int i = y1; i <= y2; i++)
            {
                setColor(im, (i - b) / k, i, col);
            }
        } else {
            for (int i = y2; i <= y1; i++)
            {
                setColor(im, (i - b) / k, i, col);
            }
        }
        return;
    }
    if ((y2 - y1 != 0)&&(x2 - x1 == 0))
    {
        if (y1 < y2)
        {
            for (int i = y1; i <= y2; i++)
            {
                setColor(im, x1, i, col);
            }
        } else {
            for (int i = y2; i <= y1; i++)
            {
                setColor(im, x1, i, col);
            }
        }
        return;
    }
    if ((y2 - y1 == 0)&&(x2 - x1 != 0))
    {
        if (x1 < x2)
        {
            for (int i = x1; i <= x2; i++)
            {
                setColor(im, i, y1, col);
            }
        } else {
            for (int i = x2; i <= x1; i++)
            {
                setColor(im, i, y1, col);
            }
        }
        return;
    }
}

void getBordersOfPolygon(Image *im, Vec3f *lowestCoords, Vec3f *highestCoords, Vec3f vertexes[], int countOfCoords)
{
	highestCoords->x = vertexes[0].x;
	highestCoords->y = vertexes[0].y;
	lowestCoords->x = vertexes[0].x;
	lowestCoords->y = vertexes[0].y;
	for (int i = 0; i < countOfCoords; i++)
	{
		if (vertexes[i].x > highestCoords->x) { highestCoords->x = vertexes[i].x; }
		if (vertexes[i].y > highestCoords->y) { highestCoords->y = vertexes[i].y; }
		if (vertexes[i].x < lowestCoords->x) { lowestCoords->x = vertexes[i].x; }
		if (vertexes[i].y < lowestCoords->y) { lowestCoords->y = vertexes[i].y; }
	}
	if (lowestCoords->x < 0) lowestCoords->x = 0;
	if (lowestCoords->y < 0) lowestCoords->y = 0;
	if (highestCoords->x > im->width - 1) highestCoords->x = im->width - 1;
	if (highestCoords->y > im->height - 1) highestCoords->y = im->height - 1;
}

Vec3f getBaricentricCoords(Vec3f vec1, Vec3f vec2, Vec3f vec3, int currX, int currY)
{
    Vec3f a; a.x = vec3.x - vec1.x; a.y = vec2.x - vec1.x; a.z = vec1.x - currX;
    Vec3f b; b.x = vec3.y - vec1.y; b.y = vec2.y - vec1.y; b.z = vec1.y - currY;
    Vec3f u = vec_vectorProduct(a, b);
	Vec3f f; f.x = 1.0 - (u.x + u.y) / u.z; f.y = u.y / u.z; f.z = u.x / u.z;
	return f;
}

void drawTriangle(Image *im, Vec3f vertexes[], float powerOfLight, int depth[], int zbufferWidth, Image texture, Vec3f textureAngles[], Image normals, Vec3f vecLight)
{
	Color colFill;

	Vec3f lowestCoords;
	Vec3f highestCoords;

	getBordersOfPolygon(im, &lowestCoords, &highestCoords, vertexes, 3);

	for (int i = lowestCoords.y; i <= highestCoords.y; i++)
	{
		for (int j = lowestCoords.x; j <= highestCoords.x; j++)
		{
			Vec3f f = getBaricentricCoords(vertexes[0], vertexes[1], vertexes[2], j, i);
			if ((f.x >= 0)&&(f.y >= 0)&&(f.z >= 0))
			{ 
				float currentDepth = f.x * vertexes[0].z + f.y * vertexes[1].z + f.z * vertexes[2].z;
				if (depth[(zbufferWidth * i) + j] < currentDepth)
				{
					Vec3f uvP;
					uvP.x = (int)(f.x * textureAngles[0].x + f.y * textureAngles[1].x + f.z * textureAngles[2].x);
					uvP.y = (int)(f.x * textureAngles[0].y + f.y * textureAngles[1].y + f.z * textureAngles[2].y);
					
					Vec3f vnP;
					vnP.x = (float)getColor(normals, uvP.x, uvP.y).r / 255.0 * 2.0 - 1.0;
					vnP.y = (float)getColor(normals, uvP.x, uvP.y).g / 255.0 * 2.0 - 1.0;
					vnP.z = (float)getColor(normals, uvP.x, uvP.y).b / 255.0 * 2.0 - 1.0;
					
					float lightCoefficient = vec_scalarProduct(vec_normilize(vecLight), vec_normilize(vnP));
					if (lightCoefficient < 0)
					{
						//continue;
						lightCoefficient = 0;
					}
					
					//printf("%f %f     %f %f\n", uvP.x, uvP.y, vnP.x, vnP.y);
					colFill = getColor(texture, uvP.x, uvP.y);
					colFill.r = (colFill.r * powerOfLight) * lightCoefficient + (colFill.r * (1 - powerOfLight)); 
					colFill.g = (colFill.g * powerOfLight) * lightCoefficient + (colFill.g * (1 - powerOfLight)); 
					colFill.b = (colFill.b * powerOfLight) * lightCoefficient + (colFill.b * (1 - powerOfLight)); 
					setColor(im, j, i, colFill);
					depth[(zbufferWidth * i) + j] = currentDepth;
				}
			}
		}
	}
}
