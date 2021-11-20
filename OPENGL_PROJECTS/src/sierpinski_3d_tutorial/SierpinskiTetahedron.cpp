#include "SierpinskiTetrahedron.h"

// PRIVATE METHODS
void SierpinskiTetrahedron::sierp_tetra(float x, float y, float z, float h, int depth)
{
	if (depth >= max_depth_)
	{
		// last size of the vertices buffer
		unsigned int ls = static_cast<unsigned int>(vertices.size()) / 3u;
		// inserting vertices
		vertices.insert(vertices.end(), { x, y, z });
		vertices.insert(vertices.end(), { x + h, y, z });
		vertices.insert(vertices.end(), { x + h/2, y, z + (h*sqrt(3.0f)/2) });
		vertices.insert(vertices.end(), { x + h/2, y + h*sqrt(6.0f)/3, z + h*(sqrt(3.0f)/6) });
		// constructing indices for the triangles
		indices.insert(indices.end(), { ls + 0u, ls + 1u, ls + 2u });
		indices.insert(indices.end(), { ls + 0u, ls + 1u, ls + 3u });
		indices.insert(indices.end(), { ls + 0u, ls + 2u, ls + 3u });
		indices.insert(indices.end(), { ls + 1u, ls + 2u, ls + 3u });
		return;
	}
	sierp_tetra(x, y, z, h / 2, depth + 1);
	sierp_tetra(x + h/2, y, z, h / 2, depth + 1);
	sierp_tetra(x + h/4, y, z + h*(sqrt(3.0f)/4), h / 2, depth + 1);
	sierp_tetra(x + h/4, y + h*(sqrt(6.0f)/6), z + h*(sqrt(3.0f)/12), h / 2, depth + 1);
}



// PUBLIC METHODS
SierpinskiTetrahedron::SierpinskiTetrahedron()
{
	max_depth_ = 0;
}

void SierpinskiTetrahedron::generate()
{
	std::cout << "Ingrese la profundidad del tetraedro de sierpinski: ";
	std::cin >> max_depth_;

	float p = -0.8f, q = -0.8f, h = 1.6f;
	std::cout << "Espere mientras generamos el tetrahedro...\n";
	sierp_tetra(p, 0.0f, q, h, 1);
	std::cout << "Tetrahedro terminado...\n";
}


SierpinskiTetrahedron::~SierpinskiTetrahedron() 
{
	vertices.clear();
	indices.clear();
}