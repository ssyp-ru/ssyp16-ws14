#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageWork.h"
#include "modelWork.h"
#include "geometry.h"
#include "graphicalLibrary.h"
#include "matrix.h"

Matrix viewport, modelView;

int width = 800, height = 800;

Vec3f vecLight  = {1, 2, 1};
Vec3f up        = {0, 1, 0}; 
Vec3f eye       = {2, 1, 3}; 
Vec3f center    = {0, 0, 0};

int main()
{
	Image normals;
	openImage(&normals, "data/african_head_nm.tga");
	//openImage(&normals, "alduin_nm.tga");

	Image texture;
	openImage(&texture, "data/african_head_diffuse.tga");
	//openImage(&texture, "alduin_diffuse.tga");

	int zbuffer[width * height];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			zbuffer[(i * width) + j] = 0;
		}
	}
	Scene mdl;
	int fileIsFounded = fillModel(&mdl, "data/african_head.obj");
	//int fileIsFounded = fillModel(&mdl, "alduin.obj");
	if (fileIsFounded == 0)
	{
		printf("this .obj file is not founded. Render stopped.\n");
		return 0;
	}
	

	Image *im;
	im = createImage(width, height, 3);
	flipVertically(&texture);
	flipVertically(&normals);
	for (int i = 0; i < mdl.countOfF; i++)
	{
		Vec3f textureAngles[3];
		textureAngles[0].x = getTexturePoint(&mdl, i, 0).x * texture.width; textureAngles[0].y = getTexturePoint(&mdl, i, 0).y * texture.height;
		textureAngles[0].z = 0;
		textureAngles[1].x = getTexturePoint(&mdl, i, 1).x * texture.width; textureAngles[1].y = getTexturePoint(&mdl, i, 1).y * texture.height;
		textureAngles[1].z = 0;
		textureAngles[2].x = getTexturePoint(&mdl, i, 2).x * texture.width; textureAngles[2].y = getTexturePoint(&mdl, i, 2).y * texture.height;
		textureAngles[2].z = 0;
		
		
		Vec3f v1 = getPoint(&mdl, i, 0);
		Vec3f v2 = getPoint(&mdl, i, 1);
		Vec3f v3 = getPoint(&mdl, i, 2);
		

		viewPort(width*3/4, height*3/4, width/8, height/8);
		lookat(center, eye, up);

		Matrix vecmat1; Matrix vecmat2; Matrix vecmat3;
		Matrix vecres1; Matrix vecres2; Matrix vecres3;
		matrix_initialize(&vecmat1, 4, 1); matrix_initialize(&vecres1, 4, 1);
		matrix_initialize(&vecmat2, 4, 1); matrix_initialize(&vecres2, 4, 1);
		matrix_initialize(&vecmat3, 4, 1); matrix_initialize(&vecres3, 4, 1);
		VectorM(v1, &vecmat1); 
		VectorM(v2, &vecmat2);
		VectorM(v3, &vecmat3);
	

		Matrix *arrayM[3] = {&viewport, &modelView, &vecmat1};
		matrix_list_multiplication(arrayM, 3, &vecres1);
		arrayM[2] = &vecmat2;
		matrix_list_multiplication(arrayM, 3, &vecres2);
		arrayM[2] = &vecmat3;
		matrix_list_multiplication(arrayM, 3, &vecres3);
		
		Vec3f vertexes[3] = { 	matrix2vector(&vecres1),
					matrix2vector(&vecres2),
					matrix2vector(&vecres3)};

		drawTriangle(im, vertexes, 0.8, zbuffer, width, texture, textureAngles, normals, vecLight);  
	}
	flipVertically(im);
	saveImage(im, "output.tga");

	return 0;
}
