#version 330

in vec3 a_Position;
in vec4 a_Color;

uniform float u_Scale;

uniform vec2 u_startPoint;
uniform vec2 u_endPoint;

out vec4 v_Color;

void main()
{
	// �����ѵ� �׸���
	float xValue = -10.f;
	float yValue = -10.f;

	// �������� ������ �̾��ִ� vector
	vec2 k = u_endPoint - u_startPoint;

	// ���� ������ ��ġ ���� ( ������ ���� k��� �ӵ��� ������ u_Scale �ð��� ������ ���� ��ġ )
	// vec2 curr = u_startPoint + k*u_Scale;

	// angle ���ϱ�
	// �� ���Ͱ� �̷�� ���̰�
	vec2 base = vec2(1,0);										// �κ����� �ϳ� (1,0) �⺻����
	float temp = dot(k, base);									// ����
	float magA = sqrt ( k.x * k.x + k.y * k.y );				// �и� 1
	float magB = sqrt ( base.x * base.x + base.y * base.y );	// �и� 2
	temp = temp / (magA * magB);								// temp�� cos(a) ��
	float angle = acos(temp);									// acos �� ���ؼ� angle�� ����


	// �ð��� Ư���϶� ���������� �����ȴ�.
	if (u_Scale > a_Position.x)
	{
		float newTime = u_Scale - a_Position.x; // ��ƼŬ�� �����ϰ� �� ���� �ð� ( 0 ~ 2sec )
		newTime = fract(newTime/2);				// 0~2���̷� ��� �Դٰ��� �ϵ��� ����� ��� (�ð��� ��� �����Ѵ�.)
												// fract(newTime/2)*2 ���� * 2 �� ���� �� ������ ������ ���ư���.

		xValue = u_startPoint.x + k.x * newTime;
		yValue = u_startPoint.y + k.y * newTime + (sin(newTime * 3.141592 * a_Position.y) * a_Position.z * 0.3f);
	}

	gl_Position = vec4(
		xValue,
		yValue,
		0.f,
		1.0f
	);

	v_Color = a_Color;
}

/*
�ǽ� 1
Vertex�� ���Ʒ��� �������� Sin � ���·� �̵��ϱ�

���� sin �Լ�

sin(a_Position.x * 3.141592 * 2 + u_Scale) * 0.2

a_Position.x �� -1���� 1
�ű⿡ 3.14 ��, ���̸� ���� (-���� ~ ����) �¿� �ֱ⸦ �ǹ� * 2�� �ؼ� (-2���� ~ 2����)
u_Scale ���� ���ؼ� �ð��� ����
���Ʒ� ���� ���� 0.2 �� ����


������ ����
(1 - (a_Position.x+1/2))

���� ����
(a_Position.x+1/2)

	// ���� �ڵ�
	float xValue = a_Position.x; // -1 ~ 1
	float yValue = sin(a_Position.x * 3.141592 * 8 + u_Scale) * 0.2 * ( ((a_Position.x+1/2)) * 2 );

	gl_Position = vec4(
		xValue,
		yValue,
		a_Position.z,
		1.0f
	);
	
	//�ǽ� 1

	//Vertex�� ���Ʒ��� �������� Sin � ���·� �̵��ϱ�
	//float xValue = a_Position.x; // -1 ~ 1
	//float yValue = sin(a_Position.x * 3.141592 * 8 + u_Scale) * 0.2 * ( ((a_Position.x+1/2)) * 2 );
	
	// �ǽ�2
	// Vertex �ϳ��� ���� Sin � ���·� �̵��ϱ�

	// �ǽ� 3
	// ���� �ٸ� �ð��� �ٸ� ��ġ�� sin���� �׸���
*/