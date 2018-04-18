#version 430
layout(location = 0) in vec3 aPos;

void main()
{
	//This is what gl_Position is assinged
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}