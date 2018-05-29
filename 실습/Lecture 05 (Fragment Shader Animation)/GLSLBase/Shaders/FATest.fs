#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Pos;

uniform float u_Time;
uniform vec2 u_CenterPosition[4];

const float pi = 3.141592;

void main()
{
	
	FragColor = vec4(0);

	// API �����
	// ������ �������� ���������� �� �׸���
	for(int i = 0; i < 4; ++i){
		vec2 pos = v_Pos;
		vec2 center = u_CenterPosition[i];

		float distance = length(pos - center) * 2 * pi;	// ���� ��ǥ�� 0,0 ������ �Ÿ��� ���ϴ� ��
		
		FragColor += vec4(sin(distance * 8.f - u_Time) * clamp(1-distance/(2*pi), 0, 1));
	}


	// �� �׸���
	/*
	float x = v_Pos.x;
	float y = v_Pos.y;
	float r = 1.f;
	
	if ( (x*x + y*y) == r*r || (x*x + y*y) < r*r && (x*x + y*y) > 0.9f)
		FragColor = vec4(1.f, 1.f, 0.f, 1.f);
	else
		FragColor = vec4(0.f, 0.f, 0.f, 1);
	*/

	// Sin �
	// ���� x ���� ������ -1 ~ 1�̹Ƿ� +1 * pi�� �ؼ� 0 ~ 2pi �ֱ�� ������ ����
	// sin(x)�� �ϰ� �Ǹ� �ش� x ���� �� �� �ִ�.
	/*
	x = (x + 1) * pi;
	float sinx = sin(x + u_Time) * 0.5f;
	
	if ( sinx + 0.05 > y  && sinx - 0.05 < y)
		FragColor = vec4(1.f, 1.f, 0.f, 1.f);
	else 
		FragColor = vec4(0.f, 0.f, 0.f, 1);
	*/
	
	// Gray Color Ȯ���ϱ�
	/*
	float sinx = pow (abs(sin(x * pi * 4)), 1);	// pow�� �ϸ� �������.
	float siny = pow (abs(sin(y * pi * 4)), 1);
	FragColor = vec4(siny, siny, siny, 1);
	*/
}

/*

Fragment Shader������ �ش� �ȼ��� �̵��� �� ����. (Frame Buffer �� �����Ǿ� �ִ� ��)
�̹� ������ ���̴�. ��, Color ���� ���� �� ���� �ִ�. 
�ű�� ������ Vertex Shader���� �ؾ� �Ѵ�.

Fragment Shader�� 2D �̴�.

*/