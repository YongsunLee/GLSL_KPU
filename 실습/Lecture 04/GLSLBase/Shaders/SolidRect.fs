#version 330

layout(location=0) out vec4 FragColor;

//in float v_Value;

in vec2 v_Value;

uniform float u_Scale;

void main()
{
	// ù��° ��ǲ�� 0
	// 0~1������ ���� ��� �Ѿ�´�.
	//
	// Sin ��� �̿��ϱ� ���� (0~1������ ��)
	float PrintValue = (sin(u_Scale) + 1.0f) / 2.0f;
	//
	// �׳� u_Scale ���� 0~1������ ������ �Ѱ��־ �ȴ�.
	//
	//if (v_Value > PrintValue -0.1f && v_Value < PrintValue +0.1f)
	//	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	//else
	//	FragColor = vec4(0);

	// ���� ����
	if ((v_Value.x * v_Value.x + v_Value.y * v_Value.y) < 0.25f)
		FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f) * vec4(PrintValue,PrintValue,PrintValue, 1.0f);
	else	// ���� �ٱ���
		FragColor = vec4(0);
		

}
