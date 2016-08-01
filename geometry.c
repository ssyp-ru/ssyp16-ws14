#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geometry.h"

Vec3f vec_sum(Vec3f vec1, Vec3f vec2)
{
	Vec3f newVec;
	newVec.x = vec1.x + vec2.x;
	newVec.y = vec1.y + vec2.y;
	newVec.z = vec1.z + vec2.z;
	return newVec;
}

Vec3f vec_sub(Vec3f vec1, Vec3f vec2)
{
	Vec3f newVec;
	newVec.x = vec1.x - vec2.x;
	newVec.y = vec1.y - vec2.y;
	newVec.z = vec1.z - vec2.z;
	return newVec;
}

Vec3f vec_scalarMultiply(Vec3f vec, float mult)
{	
	Vec3f newVec;
	newVec.x = vec.x * mult;
	newVec.y = vec.y * mult;
	newVec.z = vec.z * mult;
	return newVec;
}

float vec_scalarProduct(Vec3f vec1, Vec3f vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vec3f vec_vectorProduct(Vec3f vec1, Vec3f vec2)
{
	Vec3f newVec;
	newVec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	newVec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	newVec.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return newVec;
}

float vec_getLength(Vec3f vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Vec3f vec_normilize(Vec3f vec)
{
	float length = vec_getLength(vec);	
	Vec3f newVec;
	newVec.x = vec.x / length;
	newVec.y = vec.y / length;
	newVec.z = vec.z / length;
	return newVec;
}

void vec_printVector(Vec3f vec)
{
	printf("%f %f %f\n", vec.x, vec.y, vec.z);
}
