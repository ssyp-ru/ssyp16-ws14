#pragma once
#include "geometry.h"

#define N 5000

typedef struct ModelStruct
{
	Vec3f v[N];
	Vec3f vt[N];
	Vec3f vn[N];
	int facesV[N][3];
	int facesVT[N][3];
	int facesVN[N][3];
	int countOfV;
	int countOfVT;
	int countOfVN;
	int countOfF;
	int faces[N][3];
} Scene;

int fillModel(Scene *M, char *nameOfObjFile);
Vec3f getPoint(Scene *M, int polygonIndex, int vertexIndex);
Vec3f getTexturePoint(Scene *M, int polygonIndex, int angleIndex);
Vec3f getVertexNormal(Scene *M, int polygonIndex, int vertexIndex);
void showModel(Scene *M, int countOfV, int countOfVT, int countOfVN, int countOfF);
