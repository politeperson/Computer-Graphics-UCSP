#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 matTrans;
out vec3 colour;

void main()
{
	gl_Position = matTrans * vec4(aPos, 1.0);
	
	colour = aColor;
}