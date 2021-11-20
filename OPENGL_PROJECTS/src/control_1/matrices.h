#pragma once
#ifndef MATRICES_H_
#define MATRICES_H_
#include <iostream>

#define PI 3.141592653f

float radians(float degrees);
// multiplica una matriz de 4x4 y una de 4x1, y guarda el resultado en rslt
void MatMul(float mat1[][4], float mat2[][1], float rslt[][1]);
// copy 4x4 matrix A into B
void copy_mat(float A[][4], float B[][4]);
// recibe una matriz de 4x4 y un factor de escalamiento
void uniform_scaling(float mat[][4], float scaling);
// recibe una matriz de 4x4, un ángulo de rotación (en radianes), y un vector sobre el cual se rotará
void rotation(float mat[][4], float angle, float v[3]);
// recibe una matriz de 4x4 y un vector de traslación
void translation(float mat[][4], float v[3]);


#endif //REGULAR_POLYGON_H
