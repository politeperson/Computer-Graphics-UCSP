#include "vertices_indices_flor_2.h"

float flor_2_pol_pet_cen(float x)
{
	float a = -14.4033f, b = -8.89506, c = -1.02633;
	return a * (x * x) + b * x + c;
}
float flor_2_pol_pet_izq(float x)
{
	float a = -6.85286f, b = -6.2595f, c = -1.14689f;
	return a * (x * x) + b * x + c;
}
float flor_2_pol_pet_der(float x)
{
	float a = -6.65224f, b = -2.13988f, c = 0.110917f;
	return a * (x * x) + b * x + c;
}
float flor_2_pol_pet_inf(float x)
{
	float a = -468154.0f, b = -1.15029f*powf(10,6), c = -1.21019f*pow(10,6), d = -711278.0f, e = -254972.0f, 
		f = -56918.8f, g = -7685.98f, h = -567.439f, i = -17.0948f;
	return a * powf(x, 8) + b * powf(x, 7) + c * powf(x, 6) + d * powf(x, 5) + e * powf(x, 4) + f * powf(x, 3) + g * (x * x) + h * x + i;
}


// polinomios para las hojas
float flor_2_pol_hoja_der(float x)
{
	float a=-4.266f, b=-0.73611f, c=-0.115581f;
	return a * (x * x) + b * x + c;
}
float flor_2_pol_hoja_izq(float x) 
{
	float a=-3.39764f, b=-3.84429f, c=-1.18082f;
	return a * (x * x) + b * x + c;
}
float flor_2_pol_hoja_inf(float x)
{
	float a=115522.0f, b=280346.0f, c=278337.0f, d=145611.0f, e=42977.4f, 
		f=7064.59f, g=592.84f, h=22.5279f, i=0.0768703f;
	return a * powf(x, 8) + b * powf(x, 7) + c * powf(x, 6) + d * powf(x, 5) + e * powf(x, 4) + 
		f * powf(x, 3) + g * (x * x) + h * x + i;
}

void flor_2_generar_petalos(std::vector<float>& vert, std::vector<unsigned int>& inds)
{
	// agregando los vértices
	const int n_partes = 30;
	float left = -0.39f, right = -0.228f;
	float h = fabs(right - left) / n_partes;
	float pivot = left;
	// pétalo central, total: n_partes + 1
	for(int i = 1; i <= n_partes+1; ++i)
	{
		vert.push_back(pivot);//x
		vert.push_back(flor_2_pol_pet_cen(pivot));//y
		vert.push_back(0.0f);//z
		pivot += h;
	}
	
	left = -0.31f, right = -0.106f;
	h = fabs(right - left) / n_partes;
	pivot = left;
	// pétalo derecho, total: 2*(n_partes + 1)
	for (int i = 1; i <= n_partes + 1; ++i)
	{
		vert.push_back(pivot);//x
		vert.push_back(flor_2_pol_pet_der(pivot));//y
		vert.push_back(0.0f);//z
		pivot += h;
	}

	left = -0.514f, right = -0.31f;
	h = fabs(right - left) / n_partes;
	pivot = left;
	// pétalo izquierdo, total: 3*(n_partes + 1)
	for (int i = 1; i <= n_partes + 1; ++i)
	{
		vert.push_back(pivot);//x
		vert.push_back(flor_2_pol_pet_izq(pivot));//y
		vert.push_back(0.0f);//z
		pivot += h;
	}

	left = -0.514f, right = -0.106f;
	h = fabs(right - left) / n_partes;
	pivot = left;
	// pétalo inferior, total: 4*(n_partes + 1)
	for (int i = 1; i <= n_partes + 1; ++i)
	{
		vert.push_back(pivot);//x
		vert.push_back(flor_2_pol_pet_inf(pivot));//y
		vert.push_back(0.0f);//z
		pivot += h;
	}

	// agregando los índices
	// líneas
	// pétalo central
	inds.push_back(0);//punto inicial
	for (int i = 1; i <= n_partes-1; ++i)
	{
		inds.push_back(i);
		inds.push_back(i);
	}
	inds.push_back(n_partes);//punto final
	// offset: 2*(n_partes-1) + 2 = 60
	// pétalo derecho
	inds.push_back(n_partes + 1);//punto inicial
	for (int i = 1; i <= n_partes - 1; ++i)
	{
		inds.push_back(n_partes + 1 + i);
		inds.push_back(n_partes + 1 + i);
	}
	inds.push_back(2*(n_partes + 1) - 1);//punto final
	// offset: 4*(n_partes-1) + 4 = 120
	// pétalo izquierdo
	inds.push_back(2*(n_partes + 1));//punto inicial
	for (int i = 1; i <= n_partes - 1; ++i)
	{
		inds.push_back(2*(n_partes + 1) + i);
		inds.push_back(2*(n_partes + 1) + i);
	}
	inds.push_back(3 * (n_partes + 1) - 1);//punto final
	// offset: 6*(n_partes-1) + 6 = 180
	// pétalo inferior
	inds.push_back(3 * (n_partes + 1));//punto inicial
	for (int i = 1; i <= n_partes - 1; ++i)
	{
		inds.push_back(3 * (n_partes + 1) + i);
		inds.push_back(3 * (n_partes + 1) + i);
	}
	inds.push_back(4 * (n_partes + 1) - 1);//punto final
	// offset: 8*(n_partes-1) + 8 = 240


	// líneas_strip
	// pétalo central
	for (int i = 0; i <= n_partes; ++i)
		inds.push_back(i);
	// offset: 240 + n_partes + 1 = 271
	
	// pétalo derecho
	for (int i = 0; i <= n_partes; ++i)
		inds.push_back(n_partes + 1 + i);
	// offset: 240 + 2*(n_partes + 1) = 302
	
	// pétalo izquierdo
	for (int i = 0; i <= n_partes; ++i)
		inds.push_back(2 * (n_partes + 1) + i);
	// offset: 240 + 3*(n_partes + 1) = 333
	// pétalo inferior
	for (int i = 0; i <= n_partes; ++i)
		inds.push_back(3 * (n_partes + 1) + i);
	// offset: 240 + 4*(n_partes + 1) = 364

	return;
}

void flor_2_generar_hojas(std::vector<float>& vert, std::vector<unsigned int>& inds)
{
	// agregando los vértices
	const int n_partes = 30;
	float left = -0.315f, right = -0.011f;
	float h = fabs(right - left) / n_partes;
	float pivot = left;
	// hoja derecha, total: n_partes + 1
	for (int i = 1; i <= n_partes + 1; ++i)
	{
		vert.push_back(pivot);//x
		vert.push_back(flor_2_pol_hoja_der(pivot));//y
		vert.push_back(0.0f);//z
		pivot += h;
	}

	left = -0.613f, right = -0.315f;
	h = fabs(right - left) / n_partes;
	pivot = left;
	// hoja izquierda, total: 2*(n_partes + 1)
	for (int i = 1; i <= n_partes + 1; ++i)
	{
		vert.push_back(pivot);//x
		vert.push_back(flor_2_pol_hoja_izq(pivot));//y
		vert.push_back(0.0f);//z
		pivot += h;
	}

	left = -0.613f, right = -0.011f;
	h = fabs(right - left) / n_partes;
	pivot = left;
	// hoja inferior, total: 3*(n_partes + 1)
	for (int i = 1; i <= n_partes + 1; ++i)
	{
		vert.push_back(pivot);//x
		vert.push_back(flor_2_pol_hoja_inf(pivot));//y
		vert.push_back(0.0f);//z
		pivot += h;
	}

	// añadiendo los índices
	// líneas
	// hoja derecha
	inds.push_back(0);//punto inicial
	for (int i = 1; i <= n_partes - 1; ++i)
	{
		inds.push_back(i);
		inds.push_back(i);
	}
	inds.push_back(n_partes);//punto final
	// offset: 2*(n_partes-1) + 2 = 60
	
	// hoja izquierda
	inds.push_back(n_partes + 1);//punto inicial
	for (int i = 1; i <= n_partes - 1; ++i)
	{
		inds.push_back(n_partes + 1 + i);
		inds.push_back(n_partes + 1 + i);
	}
	inds.push_back(2 * (n_partes + 1) - 1);//punto final
	// offset: 4*(n_partes-1) + 4 = 120

	// hoja inferior
	inds.push_back(2*(n_partes + 1));//punto inicial
	for (int i = 1; i <= n_partes - 1; ++i)
	{
		inds.push_back(2*(n_partes + 1) + i);
		inds.push_back(2*(n_partes + 1) + i);
	}
	inds.push_back(3 * (n_partes + 1) - 1);//punto final
	// offset: 6*(n_partes-1) + 6 = 180

	// líneas_strip
	// hoja derecha
	for (int i = 0; i <= n_partes; ++i)
		inds.push_back(i);
	// offset: 180 + n_partes + 1 = 211

	// hoja izquierda
	for (int i = 0; i <= n_partes; ++i)
		inds.push_back(n_partes + 1 + i);
	// offset: 180 + 2*(n_partes + 1) = 242

	// hoja inferior
	for (int i = 0; i <= n_partes; ++i)
		inds.push_back(2 * (n_partes + 1) + i);
	// offset: 180 + 3*(n_partes + 1) = 273
	

}
