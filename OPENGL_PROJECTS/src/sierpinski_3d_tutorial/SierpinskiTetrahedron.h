#ifndef SIERPINSKI_TETRAHEDRON_H_
#define SIERPINSKI_TETRAHEDRON_H_
#include <vector>
#include <iostream>

class SierpinskiTetrahedron
{
private:
	int max_depth_;
	void sierp_tetra(float x, float y, float z, float h, int depth);
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	SierpinskiTetrahedron();

	void generate();

	~SierpinskiTetrahedron();
};

#endif // !SIERPINSKI_TETRAHEDRON
