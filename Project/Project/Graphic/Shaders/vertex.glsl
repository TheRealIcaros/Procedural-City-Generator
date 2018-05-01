#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}

//#version 430
//layout(location = 0) in vec3 aPos;
//
//out vec3 bPos;
//
//void main()
//{
//	//This is what gl_Position is assinged
//	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//
//	bPos = gl_Position.xyz;
//}