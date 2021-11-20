#pragma once
#ifndef REGULAR_POLYGON_H
#define REGULAR_POLYGON_H
#include <vector>
#include <cmath>
#include <random>

#define PI 3.141592653f

// for external angle
float extAngle(int i, int n);
float radians(float degrees);

float randomFloat(float a, float b);
// to build regular polygon
// with three positions: x,y,z
std::vector<float> RegPolygon(float r, int n, float x = 0.0f, float y = 0.0f);


#endif //REGULAR_POLYGON_H
