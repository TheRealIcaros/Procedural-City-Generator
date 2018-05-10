#version 330 core

layout(location=0) in vec2 vertPosition;
layout(location=1) in vec4 vertUV;
layout(location=2) in float vertWidth;

out vec4 geomUV;
out float geomWidth;

void main()
{
	gl_Position = vec4(vertPosition, 0.0, 1.0);
	geomUV = vertUV;
	geomWidth = vertWidth;
}