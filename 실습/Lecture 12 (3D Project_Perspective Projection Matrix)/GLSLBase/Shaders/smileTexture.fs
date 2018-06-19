#version 330

uniform sampler2D uTexSampler;

in vec2 v_TexPos;

layout(location=0) out vec4 FragColor;

void main()
{
	//FragColor = vec4(v_TexPos.x, v_TexPos.y, 0.0f, 1.f);

	vec2 newPos;

	newPos.x = fract(v_TexPos.x * 3);
	newPos.y = (2 - floor(v_TexPos.x * 3)) / 3.f + (v_TexPos.y / 3.f);

	FragColor = texture(uTexSampler, newPos);
}

/*

floor(v_TexPos.x * 2) �� �ϸ�

ȭ�� ������ �������� 0, 1 ���� ������ �ǰ�
���⼭ 1���� �� ���� ���ָ�

1, 0 �� �ȴ�.

�� ���� ������ ������ 

0.5, 0 ���� �������� �ǰ� ���⿡ ������ 0.5(������ v_TexPos.y (0 ~ 1)�� ����) ��ŭ �����ָ� �ȴ�. 

*/