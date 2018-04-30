#version 330

uniform float u_Time;

in vec3 a_Position;
in float a_Info;

void main()
{
	// ���� 2
	// ����� �� ���
	//gl_Position = vec4(a_Position, 1);
	
	// ���� 3
	// ������ 0.5f �� ���� �˵��� ���ƶ�
	//gl_Position = vec4(sin(u_Time) * 0.5f, cos(u_Time) * 0.5f, 0, 1);

	// ���� 4
	// �ֱ� 3�� ¥�� Sin � �׸��� �������� -Pi �κ����� ����
	//float newX = fract(u_Time) * 2 - 1;	// -1 ~ 1����
	//float newY = sin(newX * 3.141592f * 3);
	//gl_Position = vec4(newX, newY, 0, 1);

	// ���� 5
	// �� �ΰ��� �ٸ� �ֱ�(0~4PI)�� �̵��ϴ� �� + ���� �ٸ� ��
	float newX = fract(u_Time) * 2 - 1;	// -1 ~ 1���� (fract * 2 �ϸ� 0 ~ 2 ������ ��)
	float newY = sin((newX + 1) * 2 * 3.141592f) * a_Info;
	gl_Position = vec4(newX, newY, 0, 1);

}
