#version 330 core
out vec4 FragColor;

in vec3 outColor;
in vec2 texCoords;

uniform bool fill;
uniform sampler2D materialTexture;

void main()
{
	if(fill) {
		FragColor = texture(materialTexture, texCoords) * vec4(outColor, 1.0);	
	}
	else {
		FragColor = vec4(outColor, 1.0);
	}
}