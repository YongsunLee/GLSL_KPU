#version 330

in vec3 a_Position;
in vec4 a_Color;

uniform float u_Time;

uniform vec2 u_startPoint;
uniform vec2 u_endPoint;

out vec4 v_Color;

void main()
{
	float pi = 3.141592;
	// �����ѵ� �׸���
	vec2 newPos = vec2(-10, -10);

	// �������� ������ �̾��ִ� vector
	vec2 k = u_endPoint - u_startPoint;

	// ���� ������ ��ġ ���� ( ������ ���� k��� �ӵ��� ������ u_Scale �ð��� ������ ���� ��ġ )
	// vec2 curr = u_startPoint + k*u_Time;

	// mat �ʱ�ȭ ����
	// �������    (x1, y1, x2, y2)
	// x1 x2
	// y1 y2
	mat2 rot = mat2(cos(pi/2), sin(pi/2), -sin(pi/2), cos(pi/2));

	// k��� vec�� �����̸鼭 size�� 1�� ����
	vec2 rotVec = normalize(rot*k);

	// �ð��� Ư���϶� ���������� �����ȴ�.
	if (u_Time > a_Position.x)
	{
		float newTime = u_Time - a_Position.x; // ��ƼŬ�� �����ϰ� �� ���� �ð� ( 0 ~ 2sec )
		newTime = fract(newTime/2);				// 0~2���̷� ��� �Դٰ��� �ϵ��� ����� ��� (�ð��� ��� �����Ѵ�.)
												// fract(newTime/2)*2 ���� * 2 �� ���� �� ������ ������ ���ư���. (0~1 ����)
		
		float temp = (sin(newTime * 3.141592 * a_Position.y) * a_Position.z * 0.3f);

		newPos = u_startPoint + k * newTime;
		newPos += rotVec * temp;
	}

	gl_Position = vec4(
		newPos.x,
		newPos.y,
		0.f,
		1.0f
	);

	v_Color = a_Color;
}