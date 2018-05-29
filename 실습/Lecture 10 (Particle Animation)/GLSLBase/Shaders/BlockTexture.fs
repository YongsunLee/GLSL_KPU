#version 330

uniform sampler2D uTexSampler;

uniform float u_repeat;
uniform float u_sheer;

in vec2 v_TexPos;

layout(location=0) out vec4 FragColor;

void main()
{
	float repeat = u_repeat;
	float sheer = u_sheer;		// ����ĭ�� 1/2 �� �������� offset�� �ְڴٴ� �ǹ�

	vec2 newPos;
	
	newPos.x = fract(  floor(v_TexPos.x * repeat) / sheer + fract(v_TexPos.x * repeat) );
	newPos.y = fract(v_TexPos.y * repeat);

	FragColor = texture(uTexSampler, newPos).bgra;
}

/*
	vec2 newPos;
	
	newPos.x = fract(  floor(v_TexPos.x * 3) / 2.f + fract(v_TexPos.x * 3) );
	newPos.y = fract(v_TexPos.y * 3);

	FragColor = texture(uTexSampler, newPos).bgra;

*/