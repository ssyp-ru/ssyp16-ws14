#pragma once

typedef struct
{
	float x, y, z;
} Vec3f;

Vec3f vec_sum(Vec3f vec1, Vec3f vec2);
Vec3f vec_sub(Vec3f vec1, Vec3f vec2);
Vec3f vec_scalarMultiply(Vec3f vec, float mult);
float vec_scalarProduct(Vec3f vec1, Vec3f vec2);
Vec3f vec_vectorProduct(Vec3f vec1, Vec3f vec2);
float vec_getLength(Vec3f vec);
Vec3f vec_normilize(Vec3f vec);
void vec_printVector(Vec3f vec);
