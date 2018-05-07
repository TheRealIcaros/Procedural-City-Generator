#version 330 core
layout(triangles)in;
layout(triangle_strip, max_vertices = 3) out;

//in vec3 bPos[];

vec3 calculateNormal(vec3 pos0, vec3 pos1, vec3 pos2)
{
	vec3 edge0 = pos0 - pos1;
	vec3 edge1 = pos2 - pos1;

	return normalize(cross(edge0, edge1));
}

void main()
{
	for(int i=0; i < gl_in.lenght(); i++)
	{
		vec3 normal = calculateNormal(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz);
		EmitVertex();
	}
	EndPrimitive();
}