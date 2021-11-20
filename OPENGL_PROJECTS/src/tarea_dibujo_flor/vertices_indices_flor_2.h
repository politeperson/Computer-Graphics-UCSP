#pragma once
#ifndef VERTICES_INDICES_FLOR_2_H_
#define VERTICES_INDICES_FLOR_2_H_
#include <vector>
#include <cmath>


// vertices para el dibujo con primitivas
static std::vector<float> vertices_flor_2
(
	{
		// primer cuadrado
		-0.867f, 0.509f, 0.0f,
		-0.623f, 0.509f, 0.0f,
		-0.623f, 0.265f, 0.0f,
		-0.867f, 0.265f, 0.0f,
		// segundo cuadrado
		-0.003f, 0.509f, 0.0f,
		 0.03f, 0.509f, 0.0f,
		 0.03f, 0.265f, 0.0f,
		-0.003f, 0.265f, 0.0f,
		// dos puntos intermedios 
		0.03f, -0.238f, 0.0f,
		0.241f, -0.238f, 0.0f,
		// tercer cuadrado
		-0.003f, -0.621f, 0.0f,
		0.238f, -0.621f, 0.0f,
		0.238f, -0.865f, 0.0f,
		-0.003f, -0.865f, 0.0f,
		// cuarto cuadrado
		-0.867f, -0.621f, 0.0f,
		-0.623f, -0.621f, 0.0f,
		-0.623f, -0.865f, 0.0f,
		-0.867f, -0.865f, 0.0f, // idx: 17

		-0.311f, -0.039f, 0.0f,
		-0.31f, -0.103f, 0.0f,
		-0.309f, -0.159f, 0.0f,
		-0.31f, -0.212f, 0.0f,
		-0.306f, -0.282f, 0.0f // ix: 22
	}
);

// indices para graficar
static std::vector<unsigned int> indices_flor_2
(
	{
		// line_strip
		// primer cuadrado
		0, 1, 2, 3, 0,
		// offset: 5
		// segundo cuadrado
		4, 5, 6, 7, 4,
		// offset: 10
		// tercer cuadrado
		10, 11, 12, 13, 10,
		// offset: 15
		// cuarto cuadrado
		14, 15, 16, 17, 14,
		// offset: 20

		// rectángulo 1
		1, 4, 7, 2, 1,
		// offset: 25
		// rectángulo 2
		// forma cuadrada
		7, 6, 8, 9, 11, 10, 7,
		// offset: 32
		// rectángulo 3
		10, 13, 16, 15, 10,
		// offset: 37
		// rectángulo 4
		15, 14, 3, 2, 15,
		// offset: 42

		// line
		// primer cuadrado
		0, 1, 1, 2, 2, 3, 3, 0,
		// segundo cuadrado
		4, 5, 5, 6, 6, 7, 7, 4,
		// tercer cuadrado
		10, 11, 11, 12, 12, 13, 13, 10,
		// cuarto cuadrado
		14, 15, 15, 16, 16, 17, 17, 14,
		// offset: 74

		// rectángulo 1
		1, 4, 4, 7, 7, 2, 2, 1,
		// rectángulo 2
		// forma cuadrada
		7, 6, 6, 8, 8, 9, 9, 11, 11, 10, 10, 7,
		// rectángulo 3
		10, 13, 13, 16, 16, 15, 15, 10,
		// rectángulo 4
		15, 14, 14, 3, 3, 2, 2, 15,
		// offset: 110

		// tallo
		// line
		18, 19, 19, 20, 20, 21, 21, 22,
		// offset: 118
		// line_strip
		18, 19, 20, 21, 22
		// offset: 123
	}	
);


// polinomios para los vértices
float flor_2_pol_pet_cen(float x);
float flor_2_pol_pet_izq(float x);
float flor_2_pol_pet_der(float x);
float flor_2_pol_pet_inf(float x);

// polinomios para las hojas
float flor_2_pol_hoja_der(float x);
float flor_2_pol_hoja_izq(float x);
float flor_2_pol_hoja_inf(float x);



void flor_2_generar_petalos(std::vector<float>& vert, std::vector<unsigned int>& inds);
void flor_2_generar_hojas(std::vector<float>& vert, std::vector<unsigned int>& inds);



#endif