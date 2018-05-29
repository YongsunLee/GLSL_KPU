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
	// 엉뚱한데 그리고
	vec2 newPos = vec2(-10, -10);

	// 시작점과 끝점을 이어주는 vector
	vec2 k = u_endPoint - u_startPoint;

	// 현재 지점의 위치 공식 ( 시작점 부터 k라는 속도를 가지고 u_Scale 시간이 지났을 때의 위치 )
	// vec2 curr = u_startPoint + k*u_Time;

	// mat 초기화 순서
	// 순서대로    (x1, y1, x2, y2)
	// x1 x2
	// y1 y2
	mat2 rot = mat2(cos(pi/2), sin(pi/2), -sin(pi/2), cos(pi/2));

	// k라는 vec에 수직이면서 size가 1인 벡터
	vec2 rotVec = normalize(rot*k);

	// 시간이 특정일때 순차적으로 생성된다.
	if (u_Time > a_Position.x)
	{
		float newTime = u_Time - a_Position.x; // 파티클이 생성하고 난 뒤의 시간 ( 0 ~ 2sec )
		newTime = fract(newTime/2);				// 0~2사이로 계속 왔다갔다 하도록 만드는 방법 (시간은 계속 증가한다.)
												// fract(newTime/2)*2 에서 * 2 를 빼야 점 찍은데 까지만 날아간다. (0~1 사이)
		
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