#version 430

in vec2 fragUV;

out vec4 finalColor;

uniform sampler2D DiffuseTexture;

void main()
{
	finalColor = texture(DiffuseTexture, fragUV);
}