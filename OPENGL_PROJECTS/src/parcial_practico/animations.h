#pragma once
#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_
#include "matrices.h"
#include <iostream>

float animation_triangle(bool pause_animation);
void animation_translation(float trans_vec[], float h, bool pause_animation);
void animation_star(float trans_vec[], float h, bool pause_animation);
void animation_rotation(float rot_vec[], float rot_mat[][4]);


#endif //REGULAR_POLYGON_H
