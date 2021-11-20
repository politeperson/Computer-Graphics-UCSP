#version 330 core
in vec3 colour;
in vec2 TexCoord;

// texture samplers
uniform sampler2D ranaTexture;

out vec4 FragColor;

void main()
{
	FragColor = texture(ranaTexture, TexCoord) * vec4(colour, 1.0);
}
