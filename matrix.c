#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geometry.h"
#include "matrix.h"

int d = 2000;
extern Matrix modelView;
extern Matrix viewport;

void matrix_initialize(Matrix * m, int w, int h){
	m->array = (float **)malloc(sizeof(float) * w);
	for (int i = 0; i < w ; i++){
		m->array[i] = (float *)malloc(sizeof(float) * h);
	}
	m->n = w;
	m->m = h;
}

void matrix_delete(Matrix * m){
	for (int i = 0; i < m->n; i++){
		free(m->array[i]);
	}
	free(m->array);
}

void matrix_sum(Matrix *arr1, Matrix *arr2, Matrix *result_sum){
	if (arr1->n != arr2->n || arr1->m != arr2->m || result_sum->n != arr1->n || result_sum->m != arr1->m){
		printf("you are stupid, sizes aren't same\n");
		return;
	}
	for (int i = 0; i < arr1->n; i++){
		for (int j = 0; j < arr1->m; j++){
			result_sum->array[i][j] = arr1->array[i][j] + arr2->array[i][j];
		}
	}
}

void matrix_sub(Matrix *arr1, Matrix *arr2, Matrix *result_sub){
	if (arr1->n != arr2->n || arr1->m != arr2->m || result_sub->n != arr1->n || result_sub->m != arr1->m){
		printf("you are stupid, sizes aren't same \n");	
		return;
	}
	for (int i = 0; i < arr1->n; i++){
		for (int j = 0; j < arr1->m; j++){
			result_sub->array[i][j] = arr1->array[i][j] - arr2->array[i][j];
		}
	}
}

void matrix_sclr(Matrix *m, float count){
	for (int i = 0; i < m->n; i++){
		for(int j = 0; j < m->m; j++){
			m->array[i][j] *= count;
		}
	}
}

void setMatrix (Matrix *m, float arr[], int w, int h){
	int index = 0;
	for (int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
			m->array[i][j] = arr[index];
			index++;
		}
	}
}

void print_Matrix(Matrix *m){
	for (int i = 0; i < m->n; i++){
		for (int j = 0; j < m->m; j++){
			printf("%f  ", m->array[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

void matrix_multiplication(Matrix *first, Matrix *second, Matrix *result){
	if(first->m != second->n){
		printf("You are still stupid, change your matrixes\n");
		return;	
	}
	if (first->n != result->n || second->m != result->m){
		printf("You are more stupid that I thought\n");
		return;
	}
	
	for (int i = 0; i < result->n; i++){
		for (int j = 0; j < result->m; j++){
			result->array[i][j] = 0;
		}
	}

	for(int i = 0; i < first->n; i++){ 
		for(int j = 0; j < second->m; j++){
			for(int k = 0; k < second->n; k++){
				result->array[i][j] += first->array[i][k] * second->array[k][j];
			}
		}
	}

}


void matrix_copy(Matrix *dest, Matrix *src){
	matrix_initialize(dest, src->n, src->m);
	for (int i = 0; i < src->n; i++){
		for(int j = 0; j < src->m; j++){
			dest->array[i][j] = src->array[i][j];
		}
	}
}

void matrix_list_multiplication(Matrix **arr, int n, Matrix *result){
	Matrix tmp;
	Matrix mhelp;
	matrix_copy(&tmp, arr[0]);
	//matrix_initialize(&tmp, arr[0]->n, arr[1]->m);

	for (int i = 1; i < n; i++){
		matrix_initialize(&mhelp, tmp.n, arr[i]->m);
		matrix_multiplication(&tmp, arr[i], &mhelp);
		//matrix_delete(&tmp);
		if(i < n - 1){
			matrix_initialize(&tmp, arr[i]->n, arr[i+1]->m);
			matrix_copy(&tmp, &mhelp);
		}
	}
	matrix_copy(result, &mhelp);
}

void lookat(Vec3f center, Vec3f eye, Vec3f up){
	Vec3f z = vec_sub(eye, center);
	Vec3f x = vec_vectorProduct(up, z);
	Vec3f y = vec_vectorProduct(z, x);

	z = vec_normilize(z);
	x = vec_normilize(x);
	y = vec_normilize(y);

	Matrix mult;
	matrix_initialize(&modelView, 4, 4);
	matrix_initialize(&mult, 1, 3);
	float array[16] = {	x.x, x.y, x.z, -center.x, 
				y.x, y.y, y.z, -center.y, 
				z.x, z.y, z.z, -center.z, 
				0, 0, 0, 1};
	setMatrix(&modelView, array, 4, 4);

}


void viewPort(int w, int h, int x, int y){
	matrix_initialize(&viewport, 4, 4);
	float array[16] = { 	w/2, 0, 0, x + w/2,
				0, h/2, 0, y + h/2,
				0, 0, d/2, d/2,
				0, 0, 0, 1};
	setMatrix(&viewport, array, 4, 4);
}

void VectorM(Vec3f vector, Matrix *result){
	if(result->n != 4 || result->m != 1){
		printf("You are stupid");
		return;
	}
	result->array[0][0] = vector.x;
	result->array[1][0] = vector.y;
	result->array[2][0] = vector.z;
	result->array[3][0] = 1;
}

Vec3f matrix2vector(Matrix *m){
	Vec3f res = { 	m->array[0][0] / m->array[3][0], 
			m->array[1][0] / m->array[3][0], 
			m->array[2][0] / m->array[3][0] };
	return res;
}

/*int main(){
	Matrix number1;
	Matrix number2;
	Matrix number3;
	Matrix number4;
	Matrix result;
	
	Vec3f up = {0, 1, 0};
	Vec3f eye = {2, 1, 3};
	Vec3f center = {0, 0, 0};

	matrix_initialize(&number1, 2, 3);
	matrix_initialize(&number2, 3, 3);
	matrix_initialize(&result, 2, 3);
	matrix_initialize(&number3, 3, 3);
	matrix_initialize(&number4, 3, 3);
	

	Matrix *arrayM[4] = {&number1, &number2, &number3, &number4};

	float array[6] = {3, 4, 6, 6, 7, 8};
	float array2[9] = {3, 2, 2, 4, 3, 1, 7, 5, 9};


	setMatrix(&number3, array2, 3, 3);
	setMatrix(&number4, array2, 3, 3);
	setMatrix(&number1, array, 2, 3);
	setMatrix(&number2, array2, 3, 3);
	list_matrix_multiplication(arrayM, 4, &result);
	print_Matrix(&result);

	int width = 800, height = 800;

	viewPort(width*3/4, height*3/4, width/8, height/8);
	lookat(center, eye, up);

	print_Matrix(&modelView);
	print_Matrix(&viewport);

	
	return 0;
}*/
