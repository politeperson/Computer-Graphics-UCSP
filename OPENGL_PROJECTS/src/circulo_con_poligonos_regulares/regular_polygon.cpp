//
// Created by saulr on 9/1/2021.
//
#include <iostream>
#include "regular_polygon.h"

// f�rmula para el �ngulo externo de un pol�gono regular
float extAngle(int i, int n) {
    return (90.0f * (static_cast<float>(n) + 2) / static_cast<float>(n)) + (360.0f / static_cast<float>(n) * static_cast<float>(i));
}
// convierte grados a radianes
float radians(float degrees)
{
    return degrees * (PI / 180.0f);
}
// genera un random float entre [a,b]
float randomFloat(float a, float b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(a, b);
    return dis(gen);
}
// m�todo para construir el pol�gono regular
// r: radio, n: lados del pol�gono, x: posici�n en x, posici�n en y
std::vector<float> RegPolygon(float r, int n, float x, float y) {
    std::vector <float> points;
    // norma del vector u_i
    float delta = r * sqrt(2) * sqrt(1 - cos(radians(360.0f / static_cast<float>(n)))); 
    float v[3] = {x + r, y, 0.0f};
    // a�adiendo el primer v�rtice
    points.push_back(v[0]), points.push_back(v[1]), points.push_back(v[2]);
    // a�adiendo un color aleatorio
    points.push_back(randomFloat(0, 1)), points.push_back(randomFloat(0, 1)), points.push_back(randomFloat(0, 1));
    
    for(int i = 0; i < n; ++i) {
        float angle = radians(extAngle(i , n));
        float u[3] = { delta * cos(angle), delta * sin(angle), 0.0f };
        v[0] += u[0]; // trasladado por p0
        v[1] += u[1]; // trasladado por p0
        v[2] += u[2]; // trasladado por p0
        // a�adiendo las posiciones
        points.push_back(v[0]), points.push_back(v[1]), points.push_back(v[2]);
        // a�adiendo un color aleatorio
        points.push_back(randomFloat(0, 1)), points.push_back(randomFloat(0, 1)), points.push_back(randomFloat(0, 1));
    }
    return points;
}