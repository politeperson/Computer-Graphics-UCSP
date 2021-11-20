#pragma once
#ifndef CONVEX_HULL_H_
#define CONVEX_HULL_H_
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <vector>

#define EPS 0.000001

struct Point
{
    float x, y;
};

bool lexical_comp(Point a, Point b);

// genera un número random
float random(float a, float b);

// GRAHAM SCAN
// true if turn left false otherwise
bool turned_left(Point a, Point b, Point c);

// true if turn right false otherwise
bool turned_right(Point a, Point b, Point c);
std::vector<Point> UpperConvexHull(std::vector<Point> S);
std::vector<Point> LowerConvexHull(std::vector<Point> S);
std::vector<Point> GrahamScan(std::vector<Point> S, int& uconv_size, int& lconv_size);


#endif //CONVEX_HULL_H_
