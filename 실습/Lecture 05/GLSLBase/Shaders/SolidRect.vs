#version 330

in vec3 a_Position;
in vec4 a_Color;

uniform float u_Scale;

out vec4 v_Color;

void main()
{
	// 엉뚱한데 그리고
	float xValue = -10.f;
	float yValue = -10.f;

	// 시간이 특정일때 순차적으로 생성된다.
	if (u_Scale + 1 > a_Position.x)
	{
		float newTime = u_Scale + 1 - a_Position.x;
		xValue = newTime - 1;
		yValue = sin(newTime * 3.141592 * a_Position.y) * a_Position.z * 0.3f;
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
실습 1
Vertex가 위아래로 움직여서 Sin 곡선 형태로 이동하기

사용된 sin 함수

sin(a_Position.x * 3.141592 * 2 + u_Scale) * 0.2

a_Position.x 가 -1에서 1
거기에 3.14 즉, 파이를 곱함 (-파이 ~ 파이) 좌우 주기를 의미 * 2를 해서 (-2파이 ~ 2파이)
u_Scale 값을 통해서 시간값 증가
위아래 높이 조절 0.2 를 곱함


오른쪽 반쪽
(1 - (a_Position.x+1/2))

왼쪽 반쪽
(a_Position.x+1/2)

	// 본문 코드
	float xValue = a_Position.x; // -1 ~ 1
	float yValue = sin(a_Position.x * 3.141592 * 8 + u_Scale) * 0.2 * ( ((a_Position.x+1/2)) * 2 );

	gl_Position = vec4(
		xValue,
		yValue,
		a_Position.z,
		1.0f
	);
	
	//실습 1

	//Vertex가 위아래로 움직여서 Sin 곡선 형태로 이동하기
	//float xValue = a_Position.x; // -1 ~ 1
	//float yValue = sin(a_Position.x * 3.141592 * 8 + u_Scale) * 0.2 * ( ((a_Position.x+1/2)) * 2 );
	
	// 실습2
	// Vertex 하나가 직접 Sin 곡선 형태로 이동하기

	// 실습 3
	// 각각 다른 시간에 다른 위치로 sin형태 그리기
*/