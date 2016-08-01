#pragma once

#include "geometry.h"

typedef struct{
	float **array;
	int n, m;
} Matrix;

void matrix_initialize(Matrix * m, int w, int h);
void matrix_delete(Matrix *m);
void matrix_sum(Matrix *arr1, Matrix *arr2, Matrix *result_sum);
void matrix_sub(Matrix *arr1, Matrix *arr2, Matrix *result_sub);
void matrix_sclr(Matrix *m, float count);
void setMatrix(Matrix *m, float arr[], int w, int h);
void print_Matrix(Matrix *m);
void matrix_multiplication(Matrix *first, Matrix *second, Matrix *result);
void matrix_copy(Matrix *dest, Matrix *src);
void matrix_list_multiplication(Matrix **arr, int n, Matrix *result);
void lookat(Vec3f center, Vec3f eye, Vec3f up);
void viewPort(int w, int h, int x, int y);
void VectorM(Vec3f vector, Matrix *result);
Vec3f matrix2vector(Matrix *m);
