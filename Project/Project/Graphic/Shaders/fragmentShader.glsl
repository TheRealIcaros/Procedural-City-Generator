#version 430

in vec4 worldPosition;
out vec4 fragment_color;

void main()
{
	//float ambientLight = 0.1f;				//The ambient-component
	//vec3 lightPosition = vec3(0, 0, -5);	//The position of the light in the scene
	//vec3 lightDirection = normalize(lightPosition - worldPosition.xyz);		//The direction the light is faceing

	//float diffuse = clamp(dot(normal.xyz, lightDirection), 0, 1);	//The diffuse-component

	fragment_color = vec4(1.0, 0.0, 0.0, 1.0f); /** (ambientLight + diffuse);*/
}