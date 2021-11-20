#pragma once
#ifndef VERTICES_INDICES_FLOR_1_H_
#define VERTICES_INDICES_FLOR_1_H_
#include <vector>
#include <cmath>

// vertices para el dibujo con primitivas
static float vertices_flor_1[] =
{
	// cuadrado 1
	0.03f, 0.785f, 0.0f,
	0.215f, 0.785f, 0.0f,
	0.215f, 0.608f, 0.0f,
	0.03f, 0.608f, 0.0f, // 3

	// cuadrado 2
	0.683f, 0.791f, 0.0f,
	0.864f, 0.791f, 0.0f,
	0.864f, 0.614f, 0.0f,
	0.683f, 0.614f, 0.0f, // 7

	// cuadrado 3
	0.684f, -0.051f, 0.0f,
	0.869f, -0.051f, 0.0f,
	0.871f, -0.239f, 0.0f,
	0.684f, -0.239f, 0.0f, // 11

	// cuadrado 4
	0.03f, -0.05f, 0.0f,
	0.215f, -0.05f, 0.0f,
	0.215f, -0.237f, 0.0f,
	0.03f, -0.237f, 0.0f, // 15

	// pétalo 1
	0.45f, 0.668f, 0.0f,
	0.438f, 0.663f, 0.0f,
	0.463f, 0.664f, 0.0f,
	0.429f, 0.655f, 0.0f,
	0.473f, 0.655f, 0.0f,
	0.418f, 0.641f, 0.0f,
	0.481f, 0.642f, 0.0f,
	0.406f, 0.624f, 0.0f,
	0.495f, 0.624f, 0.0f,
	0.391f, 0.599f, 0.0f,
	0.508f, 0.601f, 0.0f,
	0.4f, 0.584f, 0.0f,
	0.501f, 0.588f, 0.0f,
	0.408f, 0.574f, 0.0f,
	0.492f, 0.576f, 0.0f,
	0.414f, 0.562f, 0.0f,
	0.484f, 0.564f, 0.0f,
	0.425f, 0.545f, 0.0f,
	0.472f, 0.546f, 0.0f,
	0.436f, 0.527f, 0.0f,
	0.465f, 0.528f, 0.0f,
	0.453f, 0.51f, 0.0f, // 37
	// pétalo 2
	0.522f, 0.604f, 0.0f,
	0.54f, 0.615f, 0.0f,
	0.564f, 0.616f, 0.0f,
	0.596f, 0.608f, 0.0f,
	0.586f, 0.579f, 0.0f,
	0.573f, 0.555f, 0.0f,
	0.564f, 0.531f, 0.0f,
	0.556f, 0.506f, 0.0f, // 45
	0.546f, 0.472f, 0.0f,
	0.536f, 0.438f, 0.0f,
	0.515f, 0.409f, 0.0f,
	0.493f, 0.395f, 0.0f,
	0.46f, 0.382f, 0.0f,
	0.461f, 0.417f, 0.0f,
	0.46f, 0.448f, 0.0f,
	0.456f, 0.481f, 0.0f,
	0.544f, 0.579f, 0.0f,
	0.509f, 0.498f, 0.0f, // 55

	// tercer pétalo
	0.374f, 0.606f, 0.0f,
	0.354f, 0.618f, 0.0f,
	0.328f, 0.615f, 0.0f,
	0.299f, 0.603f, 0.0f,
	0.314, 0.577f, 0.0f,
	0.328f, 0.552f, 0.0f,
	0.335f, 0.528f, 0.0f,
	0.343f, 0.505f, 0.0f,
	0.351f, 0.478f, 0.0f,
	0.361f, 0.449f, 0.0f,
	0.377f, 0.417f, 0.0f,
	0.409f, 0.391f, 0.0f,
	0.347f, 0.582f, 0.0f,
	0.398f, 0.497f, 0.0f, // 69

	// tallo
	0.45f, 0.35f, 0.0f,
	0.45f, 0.32f, 0.0f,
	0.449f, 0.289f, 0.0f,
	0.449f, 0.259f, 0.0f,
	0.45f, 0.226f, 0.0f,
	0.45f, 0.2f, 0.0f,
	0.456f, 0.163f, 0.0f,
	0.446f, 0.135f, 0.0f // 77
};

// indices para graficar
static unsigned int indices_flor_1[]
{
	// triangles
	// cuadrado 1
	0, 1, 2,
	0, 3, 2,
	// cuadrado 2
	4, 5, 6,
	4, 7, 6,
	// cuadrado 3
	8, 9, 10,
	8, 11, 10,
	// cuadrado 4
	12, 13, 14,
	12, 15, 14,
	// offset: 24

	// rectángulo 1
	1, 4, 7,
	1, 2, 7,
	// rectángulo 2
	6, 9, 8,
	6, 7, 8,
	// rectángulo 3
	11, 8, 13,
	11, 14, 13,
	// rectángulo 4
	12, 3, 2,
	12, 13, 2,
	// offset: 48

	// rectángulo central
	2, 7, 8,
	2, 13, 8,
	// offset: 54 

	// pétalo central
	16, 17, 18,
	16, 19, 20,
	16, 21, 22,
	16, 23, 24,
	16, 25, 26,
	// offset: 69
	37, 25, 26,
	37, 27, 28,
	37, 29, 30,
	37, 31, 32,
	37, 33, 34,
	37, 35, 36,
	// offset: 87

	// pétalo 2
	// primer centro
	28, 54, 26,
	26, 54, 38,
	38, 54, 39,
	39, 54, 40,
	40, 54, 41,
	41, 54, 42,
	42, 54, 43,
	43, 54, 44,
	44, 54, 28,
	// offset: 114
	// segundo centro
	44, 55, 45,
	45, 55, 46,
	46, 55, 47,
	47, 55, 48,
	48, 55, 49,
	49, 55, 50,
	50, 55, 51,
	51, 55, 52,
	52, 55, 53,
	53, 55, 37,
	37, 55, 36,
	36, 55, 34,
	34, 55, 32,
	32, 55, 30,
	30, 55, 28,
	28, 55, 44,
	// offset: 162

	// pétalo 3
	// primer centro
	25, 68, 56,
	56, 68, 57,
	57, 68, 58,
	58, 68, 59,
	59, 68, 60,
	60, 68, 61,
	61, 68, 62,
	62, 68, 25,
	// offset: 186
	// segundo centro
	62, 69, 63,
	63, 69, 64,
	64, 69, 65,
	65, 69, 66,
	66, 69, 67,
	67, 69, 50,
	50, 69, 51,
	51, 69, 52,
	52, 69, 53,
	53, 69, 37,
	37, 69, 35,
	35, 69, 33,
	33, 69, 31,
	31, 69, 29,
	29, 69, 27,
	27, 69, 25,
	25, 69, 62,
	// offset = 237

	// tallo: line_strip
	50, 70, 71, 72, 73, 74, 75, 76, 77,
	// offset: 246
	
	// modo de dibujo: lineas
	// cuadrantes
		// primer cuadrado
		0,1,1,2,2,3,3,0,
		// offset: 254
		//segundo cuadrado
		4,5,5,6,6,7,7,4,
		// offset: 262
		//tercer cuadrado
		8,9,9,10,10,11,11,8,
		// offset: 270
		12,13,13,14,14,15,15,12,
		// offset: 278

		// primer rectángulo
		1,4,2,7,
		// offset: 282
		// segundo rectángulo
		7,8,6,9,
		// offset: 286
		//tercer rectángulo
		8,13,11,14,
		// offset: 290
		//cuarto rectángulo
		12,3,13,2,
		// offset: 294

	// pétalos
		// pétalo central
		25,23,23,21,21,19,19,17,17,16,16,18,18,20,20,22,22,24,24,26,
		// offset: 314
		//pétalo derecho
		37,36,36,34,34,32,32,30,30,28,28,26,26,38,38,39,39,40,40,41,
		// offset: 334
		// pétalo izquierdo
		59,58,58,57,57,56,56,25,25,27,27,29,29,31,31,33,33,35,35,37,
		// offset: 354
		// pétalo inferior
		59,60,60,61,61,62,62,63,63,64,64,65,65,66,66,67,67,50,50,49,49,48,48,47,47,46,46,45,45,44,44,43,43,42,42,41,
		// offset: 390
		// corte del centro del pétalo
		37,53,53,52,52,51,51,50,
		// offset: 398
	
	// modo de dibujo: lineas_strip
		// cuadrantes
		// cuadrado 1
		0,1,2,3,0,
		//offset:403
		//cuadrado 2
		4,5,6,7,4,
		//offset: 408
		// cuadrado 3
		8,9,10,11,8,
		//offset: 413
		//cuadrado 4
		12,13,14,15,12,
		//offset: 418

		//rectángulos
		// rectángulo 1
		1,4,7,2,1,
		//offset: 423
		//rectángulo 2
		7,6,9,8,7,
		//offset: 428
		//rectángulo 3
		8,11,14,13,8,
		//offset: 433
		//rectángulo 4
		13,12,3,2,13,
		//offset: 438

		// pétalos
		// pétalo central
		25,23,21,19,17,16,18,20,22,24,26,
		// offset: 449
		//pétalo derecho
		37,36,34,32,30,28,26,38,39,40,41,
		// offset: 460
		//pétalo izquierdo
		59,58,57,56,25,27,29,31,33,35,37,
		// offset: 471
		//pétalo inferior
		59,60,61,62,63,64,65,66,67,50,49,48,47,46,45,44,43,42,41,
		// offset: 490
		// corte del pétalo
		37,53,52,51,50,
		// offset: 495

	// modo de dibujo: poligono
		// pétalo central
		25,23,21,19,17,16,18,20,22,24,26,28,30,32,34,36,37,35,33,31,29,27,
		// offset: 517
		//pétalo derecho
		37,36,34,32,30,28,26,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,
		// offset: 540
		//pétalo izquierdo
		37,35,33,31,29,27,25,56,57,58,59,60,61,62,63,64,65,66,67,50
		// offset: 560

};


float flor_1_pol_hoja_der_inf(float x);
float flor_1_pol_hoja_der_sup(float x);

float flor_1_pol_hoja_izq_inf(float x);
float flor_1_pol_hoja_izq_sup(float x);

void generar_hojas_flor_1_triangulos(std::vector<float>& vertices, std::vector<unsigned int>& indices);
void generar_hojas_flor_1_lineas(std::vector<float>& vert, std::vector<unsigned int>& inds);

#endif