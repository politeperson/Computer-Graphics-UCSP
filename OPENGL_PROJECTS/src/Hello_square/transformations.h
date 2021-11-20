#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_

#include <iostream>

float radians(float degrees);

// Matrix Multiplication
// mat1: matriz de 4x4, mat2: matriz de 4x1, rslt: matriz de 4x1
void MatMul(float mat1[][4], float mat2[][1], float rslt[][1]);

// vertices: el conjunto puntos en R3 que deseamos trasladar
// v: el vector por el cual queremos trasladar
// n_vertices: la cantidad de vértices en el conjunto
void translation(float vertices[], float v[], int n_vertices);

// vertices: el conjunto puntos que deseamos escalar
// x: el escalamiento en el eje x
// y: el escalamiento en el eje y
// z: el escalamiento en el eje z
void scale(float vertices[], float x, float y, float z, int n_vertices);

// vertices: el conjunto puntos que deseamos rotar
void rotationX(float vertices[], float radians, int n_vertices);

// vertices: el conjunto puntos que deseamos rotar
void rotationY(float vertices[], float radians, int n_vertices);

// vertices: el conjunto puntos que deseamos rotar
void rotationZ(float vertices[], float radians, int n_vertices);

// set transformations
void chooseTransformation(float vertices[], int n_vertices);

#endif // !TRANSFORMATIONS_H_
