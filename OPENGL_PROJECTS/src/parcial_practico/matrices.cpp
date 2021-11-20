#include "matrices.h"

// convierte grados a radianes
float radians(float degrees)
{
    return degrees * (PI / 180.0f);
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

void MatMul(float mat1[][4], float mat2[][4], float rslt[][4])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rslt[i][j] = 0;
            for (int k = 0; k < 4; k++)
                rslt[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
    return;
}

void copy_mat(float A[][4], float B[][4])
{

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            B[i][j] = A[i][j];
}

void uniform_scaling(float mat[][4], float scaling)
{
    float scale_mat[4][4] = {
        { scaling, 0.0f, 0.0f, 0.0f },
        { 0.0f, scaling, 0.0f, 0.0f },
        { 0.0f, 0.0f, scaling, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    copy_mat(scale_mat, mat);
}

void rotation(float mat[][4], float angle, float v[3])
{
    float C = (1 - cos(angle)), x = v[0], y = v[1], z = v[2];

    float rotation_mat[4][4] = {
        { cos(angle) + x * x * C, x * y * C - z * sin(angle), x * z * C + y * sin(angle), 0.0f },
        { x * y * C + z * sin(angle), cos(angle) + y * y * C, y * z * C - x * sin(angle), 0.0f },
        { x * z * C - y * sin(angle), z * y * C + x * sin(angle), cos(angle) + z * z * C, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    copy_mat(rotation_mat, mat);
}

void translation(float mat[][4], float v[3])
{
    float trans_mat[4][4] = {
        { 1.0f, 0.0f, 0.0f, v[0] },
        { 0.0f, 1.0f, 0.0f, v[1] },
        { 0.0f, 0.0f, 1.0f, v[2] },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    copy_mat(trans_mat, mat);
}


