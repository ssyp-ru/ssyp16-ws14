#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modelWork.h"
#include "geometry.h"



int fillModel(Scene *M, char *nameOfObjFile)
{
	FILE *File;
	File = fopen(nameOfObjFile, "r");
	
	if (File == 0)
	{
		return 0;
	}

	char ch[10];

	char str[1000];
	int counterV = 0, counterVN = 0, counterVT = 0, counterF = 0;
	while (fgets(str, 1000, File))
	{
		if (strncmp(str, "vt", 2) == 0)
		{
			sscanf(str, "%s%f%f%f", ch, &M->vt[counterVT].x, &M->vt[counterVT].y, &M->vt[counterVT].z);
			counterVT++;
			M->countOfVT++;
		}
		if (strncmp(str, "vn", 2) == 0)
		{
			sscanf(str, "%s%f%f%f", ch, &M->vn[counterVN].x, &M->vn[counterVN].y, &M->vn[counterVN].z);
			counterVN++;
			M->countOfVN++;
		}
		if (strncmp(str, "v ", 2) == 0)
		{
			sscanf(str, "%s%f%f%f", ch, &M->v[counterV].x, &M->v[counterV].y, &M->v[counterV].z);
			counterV++;
			M->countOfV++;
		}
		if (strncmp(str, "f", 1) == 0)
		{
		
			sscanf(str, "%s%d/%d/%d%d/%d/%d%d/%d/%d", ch,
				&M->facesV[counterF][0], &M->facesVT[counterF][0], &M->facesVN[counterF][0],
				&M->facesV[counterF][1], &M->facesVT[counterF][1], &M->facesVN[counterF][1],
				&M->facesV[counterF][2], &M->facesVT[counterF][2], &M->facesVN[counterF][2]);

			M->facesV[counterF][0]--; M->facesVT[counterF][0]--; M->facesVN[counterF][0]--;
			M->facesV[counterF][1]--; M->facesVT[counterF][1]--; M->facesVN[counterF][1]--;
			M->facesV[counterF][2]--; M->facesVT[counterF][2]--; M->facesVN[counterF][2]--;


			M->countOfF++;
			counterF++;
		}
	}
	fclose(File);
	return 1;
}

Vec3f getPoint(Scene *M, int polygonIndex, int vertexIndex)
{
	return M->v[M->facesV[polygonIndex][vertexIndex]];
}

Vec3f getTexturePoint(Scene *M, int polygonIndex, int angleIndex)
{
	return M->vt[M->facesVT[polygonIndex][angleIndex]];
}

Vec3f getVertexNormal(Scene *M, int polygonIndex, int vertexIndex)
{
	return M->vn[M->facesVN[polygonIndex][vertexIndex]];
}

void showModel(Scene *M, int countOfV, int countOfVT, int countOfVN, int countOfF)
{
	for (int i = 0; i < countOfV; i++)
	{
		printf("%lf ", M->v[i].x);
		printf("%lf ", M->v[i].y);
		printf("%lf ", M->v[i].z);
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < countOfVT; i++)
	{
		printf("%lf ", M->vt[i].x);
		printf("%lf ", M->vt[i].y);
		printf("%lf ", M->vt[i].z);
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < countOfVN; i++)
	{
		printf("%lf ", M->vn[i].x);
		printf("%lf ", M->vn[i].y);
		printf("%lf ", M->vn[i].z);
		printf("\n");
	}
	for (int i = 0; i < countOfF; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", M->facesV[i][j]);
		}
		printf("               ");
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", M->facesVT[i][j]);
		}
		printf("               ");
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", M->facesVN[i][j]);
		}
		printf("\n");
	}
}
