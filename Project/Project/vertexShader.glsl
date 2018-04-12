#version 430
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_tex;

layout(binding = 3, std140) uniform uniformBlock
{
	mat4 World;
mat4 View;
mat4 Projection;
};

//out vec2 texOut;
out vec4 worldPosition;

void main()
{
	gl_Position = vec4(vertex_position, 1.0);
	worldPosition = (Projection * View * World) * gl_Position;
}