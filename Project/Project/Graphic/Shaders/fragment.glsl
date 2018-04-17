#version 430

in vec3 bPos;

out vec4 FragColor;

void main()
{
	FragColor = vec4(bPos.x, bPos.y, bPos.z, 1.0f);
	//FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}