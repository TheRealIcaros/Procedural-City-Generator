#version 430 

layout(location=0) in vec3 vertPosition;
layout(location=1) in vec2 vertUV;
layout(location=2) in vec3 vertNormal;
layout(location=3) in vec3 vertTangent;
layout(location=4) in vec3 vertBitangent;

out vec2 fragUV;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 WorldMatrices[100];

void main()
{
	gl_Position = ProjectionMatrix * ViewMatrix * WorldMatrices[gl_InstanceID] * vec4(vertPosition,1.0);
	fragUV = vertUV * vec2(1,-1);
}