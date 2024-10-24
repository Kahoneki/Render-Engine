#version 450 core

in vec2 texCoords;
out vec4 FragColour;

struct MaterialData
{
	vec4 colour;

	sampler2D texture;

	uint activePropertiesBitfield;
};

layout (binding=1, std140) uniform Material
{
	MaterialData matData;
} material;


void main()
{
	if ((material.matData.activePropertiesBitfield & 1u) != 0u) {
		FragColour = material.matData.colour;
	}
	else {
		FragColour = vec4(1.0f, 0.0f, 1.0f, 1.0f);
	}
}