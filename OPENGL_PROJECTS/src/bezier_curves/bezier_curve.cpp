#include <iostream>
#include "bezier_curve.h"


// genera un random float entre [a,b]
float randomFloat(float a, float b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(a, b);
    return dis(gen);
}

void quadraticBezier(float p0[3], float p1[3], float p2[3], float t, float pFinal[3])
{
	// x
	pFinal[0] = powf(1 - t, 2) * p0[0] +
		(1 - t) * 2 * t * p1[0] +
		t * t * p2[0];
	// y
	pFinal[1] = powf(1 - t, 2) * p0[1] +
		(1 - t) * 2 * t * p1[1] +
		t * t * p2[1];
	// z
	pFinal[2] = 0.0f; // we are in 3D, but only draws for 2D
}

void cubicBezier(float p0[3], float p1[3], float p2[3], float p3[3], float t, float pFinal[3]) 
{
	// x
	pFinal[0] = powf(1 - t, 3) * p0[0] + 
		3 * t * powf(1 - t, 2) * p1[0] + 
		3 * t * t * (1 - t) * p2[0] + 
		powf(t, 3) * p3[0];
	// y
	pFinal[1] = powf(1 - t, 3) * p0[1] +
		3 * t * powf(1 - t, 2) * p1[1] +
		3 * t * t * (1 - t) * p2[1] +
		powf(t, 3) * p3[1];
	// z
	pFinal[2] = 0.0f;
}
