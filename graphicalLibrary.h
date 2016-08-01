#pragma once

#include "geometry.h"
#include "imageWork.h"

void drawLine(Image *im, int x1, int y1, int x2, int y2, Color col);
void getBordersOfPolygon(Image *im, Vec3f *lowestCoords, Vec3f *highestCoords, Vec3f vertexes[], int countOfCoords);
Vec3f getBaricentricCoords(Vec3f vec1, Vec3f vec2, Vec3f vec3, int currX, int currY);
void drawTriangle(Image *im, Vec3f vertexes[], float powerOfLight, int depth[], int zbufferWidth, Image texture, Vec3f textureAngles[], Image normals, Vec3f vecLight);
