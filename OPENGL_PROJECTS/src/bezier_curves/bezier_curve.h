#pragma once
#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H
#include <vector>
#include <cmath>
#include <random>

#define PI 3.141592653f

float randomFloat(float a, float b);

void quadraticBezier(float p0[3], float p1[3], float p2[3], float t, float pFinal[3]);

void cubicBezier(float p0[3], float p1[3], float p2[3], float p3[3], float t, float pFinal[3]);


#endif //BEZIER_CURVE_H
