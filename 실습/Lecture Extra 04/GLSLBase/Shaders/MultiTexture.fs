#version 330

in vec2 vTexPos;

out vec4 FragColor;

uniform sampler2D uTexSampler;

void main()
{
	FragColor = texture(uTexSampler, vTexPos);
}
