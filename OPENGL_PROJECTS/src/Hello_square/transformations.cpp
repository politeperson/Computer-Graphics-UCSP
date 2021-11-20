#include "transformations.h"

float radians(float degrees)
{
    const float PI = 3.1415926535;
    return degrees * (PI / 180);
}

void MatMul(float mat1[][4], float mat2[][1], float rslt[][1])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 1; j++) {
            rslt[i][j] = 0;
            for (int k = 0; k < 4; k++)
                rslt[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
    return;
}

void translation(float vertices[], float v[], int n_vertices)
{
    // la matrix de transformación
    float trans_mat[4][4] = {
        { 1.0f, 0.0f, 0.0f, v[0] },
        { 0.0f, 1.0f, 0.0f, v[1] },
        { 0.0f, 0.0f, 1.0f, v[2] },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    
    for (int i = 0; i < 3 * n_vertices; i += 3)
    {
        float u[4][1] = { {vertices[i]}, {vertices[i + 1]}, {vertices[i + 2]}, {1.0f} };
        float rslt[4][1];
        MatMul(trans_mat, u, rslt);
        vertices[i] = rslt[0][0], vertices[i+1] = rslt[1][0], vertices[i+2] = rslt[2][0];
    }
}

// vertices: el conjunto puntos que deseamos escalar
// x: el escalamiento en el eje x
// y: el escalamiento en el eje y
// z: el escalamiento en el eje z
void scale(float vertices[], float x, float y, float z, int n_vertices)
{
    // la matrix de transformación
    float trans_mat[4][4] = {
        { x, 0.0f, 0.0f, 0.0f },
        { 0.0f, y, 0.0f, 0.0f },
        { 0.0f, 0.0f, z, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };

    for (int i = 0; i < 3 * n_vertices; i += 3)
    {
        float u[4][1] = { {vertices[i]}, {vertices[i + 1]}, {vertices[i + 2]}, {1.0f} };
        float rslt[4][1];
        MatMul(trans_mat, u, rslt);
        vertices[i] = rslt[0][0], vertices[i + 1] = rslt[1][0], vertices[i + 2] = rslt[2][0];
    }
}

// vertices: el conjunto puntos que deseamos rotar
void rotationX(float vertices[], float radians, int n_vertices)
{
    // la matrix de transformación
    float trans_mat[4][4] = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, cos(radians), -sin(radians), 0.0f },
        { 0.0f, sin(radians), cos(radians), 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };

    for (int i = 0; i < 3 * n_vertices; i += 3)
    {
        float u[4][1] = { {vertices[i]}, {vertices[i + 1]}, {vertices[i + 2]}, {1.0f} };
        float rslt[4][1];
        MatMul(trans_mat, u, rslt);
        vertices[i] = rslt[0][0], vertices[i + 1] = rslt[1][0], vertices[i + 2] = rslt[2][0];
    }
}

// vertices: el conjunto puntos que deseamos rotar
void rotationY(float vertices[], float radians, int n_vertices)
{
    // la matrix de transformación
    float trans_mat[4][4] = {
        { cos(radians), 0.0f, sin(radians), 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { -sin(radians), 0.0f, cos(radians), 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };

    for (int i = 0; i < 3 * n_vertices; i += 3)
    {
        float u[4][1] = { {vertices[i]}, {vertices[i + 1]}, {vertices[i + 2]}, {1.0f} };
        float rslt[4][1];
        MatMul(trans_mat, u, rslt);
        vertices[i] = rslt[0][0], vertices[i + 1] = rslt[1][0], vertices[i + 2] = rslt[2][0];
    }
}

// vertices: el conjunto puntos que deseamos rotar
void rotationZ(float vertices[], float radians, int n_vertices)
{
    // la matrix de transformación
    float trans_mat[4][4] = {
        { cos(radians), -sin(radians), 0.0f, 0.0f },
        { sin(radians), cos(radians), 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };

    for (int i = 0; i < 3 * n_vertices; i += 3)
    {
        float u[4][1] = { {vertices[i]}, {vertices[i + 1]}, {vertices[i + 2]}, {1.0f} };
        float rslt[4][1];
        MatMul(trans_mat, u, rslt);
        vertices[i] = rslt[0][0], vertices[i + 1] = rslt[1][0], vertices[i + 2] = rslt[2][0];
    }
}

void chooseTransformation(float vertices[], int n_vertices)
{
    int op;
    do
    {
        std::cout << "Digita el numero de la transformacion que desees: \n";
        std::cout << "1) Translation \n";
        std::cout << "2) Scaling \n";
        std::cout << "3) Rotation X \n";
        std::cout << "4) Rotation Y \n";
        std::cout << "5) Rotation Z \n";
        std::cin >> op;
    } while (op < 0 || op > 5);
    
    switch (op)
    {
        case 1:
        {
            float x, y, z;
            std::cout << "Digita el vector de traslacion (x, y, z).\n";
            std::cin >> x >> y >> z;
            float v[] = { x , y , z };
            translation(vertices, v, n_vertices);
            break;
        }
        case 2:
        {
            float x, y, z;
            std::cout << "Digita el escalamiento de cada eje (x, y, z).\n";
            std::cin >> x >> y >> z;
            scale(vertices, x,  y, z, n_vertices);
            break;
        }
        case 3:
        {
            float angle;
            std::cout << "Digita el angulo de rotacion grados.\n";
            std::cin >> angle;
            rotationX(vertices, radians(angle), n_vertices);
            break;
        }
        case 4:
        {
            float angle;
            std::cout << "Digita el angulo de rotacion degrees.\n";
            std::cin >> angle;
            rotationY(vertices, radians(angle), n_vertices);
            break;
        }
        default: {
            float angle;
            std::cout << "Digita el angulo de rotacion degrees.\n";
            std::cin >> angle;
            rotationZ(vertices, radians(angle), n_vertices);
            break;
        }
    }
    std::cout << "Transformacion finalizada :)\n";
    return;
}
