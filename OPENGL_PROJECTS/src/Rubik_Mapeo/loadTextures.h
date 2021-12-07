#pragma once
#ifndef LOAD_TEXTURES_H_
#define LOAD_TEXTURES_H_
// GLAD
#include <glad/glad.h>
#include <glfw/glfw3.h>
// stb_image
#include "stb_image.h"

#include <iostream>
#include <vector>
#include <string>


void confTexture(GLuint& textureID, std::string& texturePath);


#endif //!LOAD_TEXTURES_H_