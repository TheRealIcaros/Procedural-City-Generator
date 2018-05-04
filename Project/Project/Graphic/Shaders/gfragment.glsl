#version 430
layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec4 gNormal;
layout(location = 2) out vec4 gColorSpec;
layout(location = 3) out vec4 gColorInfo;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

in vec3 FragPos;
in vec3 FragNormal;
in vec2 FragUV;
in vec3 FragTangent;
in vec3 FragBitangent;

in vec4 FragLightSpace;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

uniform sampler2D depthMap;
uniform vec3 lightDir;

float ShadowCalc(vec4 lightSpace)
{
	//Perform perspective division
	vec3 projectionCoords = lightSpace.xyz / lightSpace.w;
	float shadow = 0.0f;
	//Change the NDC to a range of [0,1] to match depth-map range
	projectionCoords = projectionCoords * 0.5 + 0.5;
	if (projectionCoords.x == clamp(projectionCoords.x, 0.0, 1.0) && projectionCoords.y == clamp(projectionCoords.y, 0.0, 1.0))
	{
		float closestDepth = texture(depthMap, projectionCoords.xy).r;

		float currentDepth = projectionCoords.z;

		float bias = max(0.05 * (1.0 - dot(FragNormal, lightDir)), 0.005);
		shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
	}

	return shadow;
}

void main()
{
	mat3 TBN = mat3(FragTangent, FragBitangent, FragNormal);

	gPosition = FragPos;

	vec3 normalMap = texture(texture_normal1, FragUV).rgb;
	gNormal.xyz = normalize(FragNormal + (TBN * normalMap)).xyz;
	gNormal.w = ShadowCalc(FragLightSpace);

	gColorSpec.rgb = texture(texture_diffuse1, FragUV).rgb;


	gColorInfo.x = material.ambient.x;
	gColorInfo.y = material.diffuse.x;
	gColorInfo.z = material.specular.x;
	gColorInfo.a = material.shininess;
}


//#version 430
//
//in vec3 bPos;
//
//out vec4 FragColor;
//
//void main()
//{
//	FragColor = vec4(bPos.x, bPos.y, bPos.z, 1.0f);
//	//FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//}