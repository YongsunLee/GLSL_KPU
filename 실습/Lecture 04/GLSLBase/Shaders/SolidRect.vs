#version 330

// input
in vec3 a_Position;
//in vec4 a_Position;
//in vec4 a_Color;

// output
//out float v_Value;

out vec2 v_Value;

void main()
{
	// 1��
	//gl_Position = a_Position;
	//gl_Position.w = 1.0f;			// w���� 0�̸� ȭ�鿡 �׷����� �����Ƿ� 1.0���� ����
	//
	//v_Value = a_Position.w;			
	//// vs output ù��° vertex�� �ƿ�ǲ�� 0, �ι�° vertex�� �ƿ�ǲ�� 1
	//// 0�� 1�� �Ѿ���Ƿ� ������ ���� ������ �Ǿ� �Ѿ��.
	//

	// 2��
	gl_Position.xyz = a_Position;
	gl_Position.w = 1.0f;			// w���� 0�̸� ȭ�鿡 �׷����� �����Ƿ� 1.0���� ����
	
	v_Value = a_Position.xy;
}