#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in vec4 geomUV[];
in float geomWidth[];

out vec2 fragUV;

uniform mat4 ProjectionMatrix;
uniform float Height;

void main()
{
	vec2 minUV = vec2(geomUV[0].x, geomUV[0].y);
	vec2 maxUV = vec2(geomUV[0].z, geomUV[0].w);
	vec4 pos;
	
	// Top left
	pos = gl_in[0].gl_Position;
	gl_Position = ProjectionMatrix * pos;
	//fragUV = vec2(0.78, 0.01);
	fragUV = vec2(minUV.x, minUV.y);
	EmitVertex();
	
	// Bottom left
	pos = gl_in[0].gl_Position;
	pos.y += Height;
	gl_Position = ProjectionMatrix * pos;
	//fragUV = vec2(0.78, 0.13);
	fragUV = vec2(minUV.x, maxUV.y);
	EmitVertex();
	
	// Top right
	pos = gl_in[0].gl_Position;
	pos.x += geomWidth[0];
	gl_Position = ProjectionMatrix * pos;
	//fragUV = vec2(0.84, 0.01);
	fragUV = vec2(maxUV.x, minUV.y);
	EmitVertex();
	
	// Bottom right
	pos = gl_in[0].gl_Position;
	pos.x += geomWidth[0];
	pos.y += Height;
	gl_Position = ProjectionMatrix * pos;
	//fragUV = vec2(0.84, 0.13);
	fragUV = vec2(maxUV.x, maxUV.y);
	EmitVertex();

	EndPrimitive();
}