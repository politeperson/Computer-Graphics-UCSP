#include "vertices_indices_flor_1.h"



float flor_1_pol_hoja_der_inf(float x)
{
	float a = -155.679f, b = 233.601f, c = -94.831f, d = -1.13243f, e = 4.77345f;
	return a * (x * x * x * x) + b * (x * x * x) + c * (x * x) + d * x + e;
}

float flor_1_pol_hoja_der_sup(float x)
{
	float a = -9.68429f, b = 11.8508f, c = -3.26217f;
	return a * (x * x) + b * x + c;
}

float flor_1_pol_hoja_izq_inf(float x)
{
	float a = -1785.79f, b = 2527.8f, c = -1310.98f, d = 292.751f, e = -23.4141;
	return a * (x * x * x * x) + b * (x * x * x) + c * (x * x) + d * x + e;
}

float flor_1_pol_hoja_izq_sup(float x)
{
	float a = -5.50787f, b = 3.0872f, c = -0.0892386f;
	return a * (x * x) + b * x + c;
}

void generar_hojas_flor_1_triangulos(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
	int n_parts = 20;// 20 partes del dominio

	// añadiendo la hoja derecha
	// lado inferior
	float left = 0.453f, right = 0.665f;
	float h = fabs(right - left) / n_parts;
	float pivot = left;
	// añadiendo vértices
	for (int i = 1; i <= n_parts + 1; ++i)
	{
		vertices.push_back(pivot); // x
		vertices.push_back(flor_1_pol_hoja_der_inf(pivot)); // y
		vertices.push_back(0.0f); // z
		pivot += h;
	} // (n_parts + 1) vertices
	// lado superior
	left = 0.434f, right = 0.665f;
	h = fabs(right - left) / n_parts;
	pivot = left;
	for (int i = 1; i <= n_parts + 1; ++i)
	{
		vertices.push_back(pivot); // x
		vertices.push_back(flor_1_pol_hoja_der_sup(pivot)); // y
		vertices.push_back(0.0f); // z
		pivot += h;
	} // (n_parts + 1) vertices
	// añadiendo el centroide de la hoja
	// índice: 2*(n_parts + 1)
	vertices.push_back(0.521f), vertices.push_back(0.178f), vertices.push_back(0.0f);
	// total N° de vertices hasta ahora 2*(n_parts + 1) + 1(centroid)

	{
		// añadiendo los índices
		// los de la parte inferior
		for (int i = 0; i < n_parts; ++i)
		{
			indices.push_back(i);
			indices.push_back(2 * (n_parts + 1)); // el vértice centroide de la hoja
			indices.push_back(i + 1);
		}
		// los de la parte superior
		for (int i = 0; i < n_parts; ++i)
		{
			indices.push_back(n_parts + 1 + i);
			indices.push_back(2 * (n_parts + 1)); // el vértice centroide de la hoja
			indices.push_back(n_parts + 1 + i + 1);
		}
		// añadiendo el último triángulo
		indices.push_back(n_parts + 1); // left de la parte superior
		indices.push_back(2 * (n_parts + 1)); // el vertice centroide de la hoja
		indices.push_back(0); // el left de la parte inferior
	}

	// añadiendo la hoja izquierda
	// lado inferior
	left = 0.231f, right = 0.453f;
	h = fabs(right - left) / n_parts;
	pivot = left;
	// añadiendo vértices
	for (int i = 1; i <= n_parts + 1; ++i)
	{
		vertices.push_back(pivot); // x
		vertices.push_back(flor_1_pol_hoja_izq_inf(pivot)); // y
		vertices.push_back(0.0f); // z
		pivot += h;
	} // (n_parts + 1) vertices
	// lado superior
	left = 0.231f, right = 0.453f;
	h = fabs(right - left) / n_parts;
	pivot = left;
	// añadiendo vértices
	for (int i = 1; i <= n_parts + 1; ++i)
	{
		vertices.push_back(pivot); // x
		vertices.push_back(flor_1_pol_hoja_izq_sup(pivot)); // y
		vertices.push_back(0.0f); // z
		pivot += h;
	} // (n_parts + 1) vertices
	// añadiendo el centroide de la hoja
	// índice: 4*(n_parts + 1) + 1
	vertices.push_back(0.337f), vertices.push_back(0.217f), vertices.push_back(0.0f);
	// total N° de vertices hasta ahora 2*(n_parts + 1) + 1(centroid) + 2*(n_parts + 1) + 1(centroid)
	// hoja derecha y hoja izquierda

	{
		// añadiendo los índices
		// los de la parte inferior
		for (int i = 0; i < n_parts; ++i)
		{
			indices.push_back(2 * (n_parts + 1) + 1 + i);
			indices.push_back(4 * (n_parts + 1) + 1); // el vértice centroide de la hoja
			indices.push_back(2 * (n_parts + 1) + 1 + i + 1);
		}
		// los de la parte superior
		for (int i = 0; i < n_parts; ++i)
		{
			indices.push_back(3 * (n_parts + 1) + 1 + i);
			indices.push_back(4 * (n_parts + 1) + 1); // el vértice centroide de la hoja
			indices.push_back(3 * (n_parts + 1) + 1 + i + 1);
		}
		// añadiendo los últimos dos triángulos
		// primer triángulo
		indices.push_back(3 * (n_parts + 1)); // right de la parte inferior
		indices.push_back(4 * (n_parts + 1) + 1); // el vertice centroide de la hoja
		indices.push_back(n_parts + 1); // el left de la hoja derecha de la parte superior
		// segundo triángulo
		indices.push_back(n_parts + 1); // el left de la hoja derecha de la parte superior
		indices.push_back(4 * (n_parts + 1) + 1); // el vertice centroide de la hoja
		indices.push_back(4 * (n_parts + 1)); // el right de la parte superior
	}
	return;
}

void generar_hojas_flor_1_lineas(std::vector<float>& vert, std::vector<unsigned int>& inds)
{
	int n_parts = 20;// 20 partes del dominio
	// añadiendo la hoja derecha
	// lado inferior
	float left = 0.453f, right = 0.665f;
	float h = fabs(right - left) / n_parts;
	float pivot = left;
	// añadiendo vértices
	for (int i = 1; i <= n_parts + 1; ++i)
	{
		vert.push_back(pivot); // x
		vert.push_back(flor_1_pol_hoja_der_inf(pivot)); // y
		vert.push_back(0.0f); // z
		pivot += h;
	} // (n_parts + 1) vertices
	// lado superior
	left = 0.434f, right = 0.665f;
	h = fabs(right - left) / n_parts;
	pivot = left;
	for (int i = 1; i <= n_parts + 1; ++i)
	{
		vert.push_back(pivot); // x
		vert.push_back(flor_1_pol_hoja_der_sup(pivot)); // y
		vert.push_back(0.0f); // z
		pivot += h;
	} // (n_parts + 1) vertices
	// total N° de vertices hasta ahora 2*(n_parts + 1)

	// añadiendo la hoja izquierda
	// lado inferior
	left = 0.231f, right = 0.453f;
	h = fabs(right - left) / n_parts;
	pivot = left;
	// añadiendo vértices
	for (int i = 1; i <= n_parts + 1; ++i)
	{
		vert.push_back(pivot); // x
		vert.push_back(flor_1_pol_hoja_izq_inf(pivot)); // y
		vert.push_back(0.0f); // z
		pivot += h;
	} // (n_parts + 1) vertices
	// lado superior
	left = 0.231f, right = 0.453f;
	h = fabs(right - left) / n_parts;
	pivot = left;
	// añadiendo vértices
	for (int i = 1; i <= n_parts + 1; ++i)
	{
		vert.push_back(pivot); // x
		vert.push_back(flor_1_pol_hoja_izq_sup(pivot)); // y
		vert.push_back(0.0f); // z
		pivot += h;
	} // (n_parts + 1) vertices
	// total N° de vertices hasta ahora 2*(n_parts + 1) + 2*(n_parts + 1)
	// hoja derecha y hoja izquierda

	// añadiendo índices
	// hoja derecha
	// modo de dibujo: line
	// los de la parte inferior
	inds.push_back(0);//primer vertice
	for (int i = 1; i <= n_parts - 1; ++i)
	{
		inds.push_back(i);
		inds.push_back(i);
	}
	inds.push_back(n_parts); // último vértice
	// offset: 2*(n_parts - 1) + 2 = 40
	// los de la parte superior
	inds.push_back(n_parts + 1);//primer vertice
	for (int i = 1; i <= n_parts - 1; ++i)
	{
		inds.push_back(n_parts + 1 + i);
		inds.push_back(n_parts + 1 + i);
	}
	inds.push_back(2 * (n_parts + 1)); // último vértice
	// offset: 4*(n_parts - 1) + 4 = 80
	///////////////////////////////////////////////////////////////////////
	// modo de dibujo: line_strip
	// los de la parte inferior
	for (int i = 0; i <= n_parts; ++i)
		inds.push_back(i);
	// offset: 80 + (n_parts + 1) = 101
	// los de la parte superior
	for (int i = 0; i <= n_parts; ++i)
		inds.push_back(n_parts + 1 + i);
	// offset: 80 + 2*(n_parts + 1) = 122

	// hoja izquierda
	// modo de dibujo: line
	// los de la parte inferior
	inds.push_back(2*(n_parts + 1));//primer vertice
	for (int i = 1; i <= n_parts - 1; ++i)
	{
		inds.push_back(2 * (n_parts + 1) + i);
		inds.push_back(2 * (n_parts + 1) + i);
	}
	inds.push_back(3*(n_parts + 1) - 1); // último vértice
	// offset: 122 + 2*(n_parts - 1) + 2 = 162
	// los de la parte superior
	inds.push_back(3*(n_parts + 1));//primer vertice
	for (int i = 1; i <= n_parts - 1; ++i)
	{
		inds.push_back(3*(n_parts + 1) + i);
		inds.push_back(3*(n_parts + 1) + i);
	}
	inds.push_back(4 * (n_parts + 1) - 1); // último vértice
	// offset: 122 + 4*(n_parts - 1) + 4 = 202
	///////////////////////////////////////////////////////////////////////
	// modo de dibujo: line_strip
	// los de la parte inferior
	for (int i = 0; i <= n_parts; ++i)
		inds.push_back(2*(n_parts + 1) + i);
	// offset: 202 + (n_parts + 1) = 223
	// los de la parte superior
	for (int i = 0; i <= n_parts; ++i)
		inds.push_back(3*(n_parts + 1) + i);
	// offset: 202 + 2*(n_parts + 1) = 244
}
