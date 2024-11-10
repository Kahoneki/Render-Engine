#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : require

in vec2 texCoord;
out vec4 FragColour;

struct MaterialData
{
	vec4 colour;
	uint64_t textureHandle;
	uint activePropertiesBitfield;
};

layout (binding=1, std140) uniform MaterialBlock
{
	MaterialData matData;
} material;


void main()
{
	FragColour = vec4(1.0f);
	if ((material.matData.activePropertiesBitfield & 2u) != 0u) {
		FragColour = texture(sampler2D(material.matData.textureHandle), texCoord);
	}
	if ((material.matData.activePropertiesBitfield & 1u) != 0u) {
		FragColour *= material.matData.colour;
	}
}