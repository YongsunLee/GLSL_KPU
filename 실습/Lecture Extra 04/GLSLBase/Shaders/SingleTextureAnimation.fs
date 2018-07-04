#version 330

in vec2 vTexPos;

out vec4 FragColor;

uniform float uTime;

uniform sampler2D uTexSampler;

void main()
{
	vec2 newPos = vec2(vTexPos.x, uTime/6.0f + vTexPos.y/6.0f);
	FragColor = texture(uTexSampler, newPos);
}
