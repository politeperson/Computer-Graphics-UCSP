#include "animations.h"

float animation_triangle(bool pause_animation)
{
    static float h = 0.0f;
    if (!pause_animation) h += 0.001f;
    return h;
}

void animation_translation(float trans_vec[], float h, bool pause_animation)
{
    static float v0[3] = { 0.0f, 0.55f, 0.0f }, v1[3] = { -1.2f, 0.0f,0.0f };
    static float v2[3] = { 0.0f,-1.1f,0.0f }, v3[3] = { 1.2f, 0.0f, 0.0f }, v4[3] = { 0.0f,0.55f,0.0f };
    static float t0 = 0.0f, t1 = 0.0f, t2 = 0.0f, t3 = 0.0f, t4 = 0.0f;
    if (pause_animation) {
        trans_vec[0] += v1[0] * t1;
        trans_vec[0] += v3[0] * t3;
        trans_vec[1] += v0[1] * t0;
        trans_vec[1] += v2[1] * t2;
        trans_vec[1] += v4[1] * t4;
        return;
    }

    if (t0 <= 1.0f) {
        trans_vec[1] += v0[1] * t0;
        t0 += h;
        return;
    }
    if (t1 <= 1.0f) {
        trans_vec[1] += v0[1];
        trans_vec[0] += v1[0] * t1;
        t1 += h;
        return;
    }
    if (t2 <= 1.0f) {
        trans_vec[1] += v0[1];
        trans_vec[0] += v1[0];
        trans_vec[1] += v2[1] * t2;
        t2 += h;
        return;
    }
    if (t3 <= 1.0f) {
        trans_vec[1] += v0[1];
        trans_vec[0] += v1[0];
        trans_vec[1] += v2[1];
        trans_vec[0] += v3[0] * t3;
        t3 += h;
        return;
    }
    if (t4 <= 1.0f) {
        trans_vec[1] += v0[1];
        trans_vec[0] += v1[0];
        trans_vec[1] += v2[1];
        trans_vec[0] += v3[0];
        trans_vec[1] += v4[1] * t4;
        t4 += h;
        return;
    }
    trans_vec[0] = trans_vec[1] = trans_vec[2] = 0.0f; // restarting the translation vector
    t0 = t1 = t2 = t3 = t4 = 0.0f; // reiniciando los escalares
}

void animation_star(float trans_vec[], float h, bool pause_animation)
{
    static float v0[3] = { 0.0f, 0.83f, 0.0f }, v1[3] = { -1.7f, 0.0f,0.0f };
    static float v2[3] = { 0.0f, -1.66f,0.0f }, v3[3] = { 1.7f, 0.0f, 0.0f }, v4[3] = { 0.0f,0.83f,0.0f };
    static float t0 = 0.0f, t1 = 0.0f, t2 = 0.0f, t3 = 0.0f, t4 = 0.0f;
    if (pause_animation) {
        trans_vec[0] += v1[0] * t1;
        trans_vec[0] += v3[0] * t3;
        trans_vec[1] += v0[1] * t0;
        trans_vec[1] += v2[1] * t2;
        trans_vec[1] += v4[1] * t4;
        return;
    }
    
    if (t0 <= 1.0f) {
        trans_vec[1] += v0[1] * t0;
        t0 += h;
        return;
    }
    if (t1 <= 1.0f) {
        trans_vec[1] += v0[1];
        trans_vec[0] += v1[0] * t1;
        t1 += h;
        return;
    }
    if (t2 <= 1.0f) {
        trans_vec[1] += v0[1];
        trans_vec[0] += v1[0];
        trans_vec[1] += v2[1] * t2;
        t2 += h;
        return;
    }
    if (t3 <= 1.0f) {
        trans_vec[1] += v0[1];
        trans_vec[0] += v1[0];
        trans_vec[1] += v2[1];
        trans_vec[0] += v3[0] * t3;
        t3 += h;
        return;
    }
    if (t4 <= 1.0f) {
        trans_vec[1] += v0[1];
        trans_vec[0] += v1[0];
        trans_vec[1] += v2[1];
        trans_vec[0] += v3[0];
        trans_vec[1] += v4[1] * t4;
        t4 += h;
        return;
    }
    trans_vec[0] = trans_vec[1] = trans_vec[2] = 0.0f; // restarting the translation vector
    t0 = t1 = t2 = t3 = t4 = 0.0f; // reiniciando los escalares
}

void animation_rotation(float rot_vec[], float rot_mat[][4])
{
    static float vec[4][1] = { {0.3f}, {0.0f}, {0.0f}, {1.0f} }, vec_r[4][1];

    MatMul(rot_mat, vec, vec_r);

    rot_vec[0] = vec_r[0][0] - vec[0][0];
    rot_vec[1] = vec_r[1][0] - vec[1][0];
    rot_vec[2] = vec_r[2][0] - vec[2][0];
}
