#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 aRotation;
out vec3 colour;

void main()
{
	gl_Position = aRotation * vec4(aPos, 1.0);
	colour = aColor;
	TexCoord = aTexCoord;
}