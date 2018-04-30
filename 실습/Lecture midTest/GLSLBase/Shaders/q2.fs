#version 330

layout(location=0) out vec4 FragColor;

const float pi = 3.141592;

in vec2 v_Pos;

void main()
{
	// ���� 6
	//float distacne = length(v_Pos); // 0 ~ 1
	//float greyScale = sin(distacne * pi * 4);
	//FragColor = vec4(greyScale);

	// ���� 7
	//float distance1 = length(v_Pos - vec2(-1,0));
	//float distance2 = length(v_Pos - vec2(1,0));

	//if (distance1 < 1.0f || distance2 < 1.0f)
	//	FragColor = vec4(1);
	//else
	//	FragColor = vec4(0);

	// ���� 8
	float distance1 = length(v_Pos - vec2(-1,0));
	float distance2 = length(v_Pos - vec2(1,0));
	float greyScale1 = clamp(-(floor(distance1) - 1), 0, 1);	// 0 ~ 1 ������ ��
	float greyScale2 = clamp(-(floor(distance2) - 1), 0, 1);	// 0 ~ 1 ������ ��

	/*

	floor(distacne)�� ���ؼ� 0, 1, 2 ���� �����µ�
	���⼭ -1 �� �ϸ� -1 0 1 ���� ����
	���⼭ �� ��ü�� -1�� �ϸ� 1 0 -1 �� ����ǰ�
	�̰� clamp �ع�����
	1�� 1�� 0�� 0�� -1�� 0 ������ clamp

	�̰� �״�� ����ϸ� 1, 0 �� ���� ������ �ȴ�.

	*/

	FragColor = vec4(greyScale1 + greyScale2);

}

