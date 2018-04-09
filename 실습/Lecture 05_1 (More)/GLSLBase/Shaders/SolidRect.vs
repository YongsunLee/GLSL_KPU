#version 330

in vec3 a_Position;
in vec4 a_Color;

uniform float u_Scale;

uniform vec2 u_startPoint;
uniform vec2 u_endPoint;

out vec4 v_Color;

void main()
{
	// 엉뚱한데 그리고
	float xValue = -10.f;
	float yValue = -10.f;

	// 시작점과 끝점을 이어주는 vector
	vec2 k = u_endPoint - u_startPoint;

	// 현재 지점의 위치 공식 ( 시작점 부터 k라는 속도를 가지고 u_Scale 시간이 지났을 때의 위치 )
	// vec2 curr = u_startPoint + k*u_Scale;

	// angle 구하기
	// 두 벡터가 이루는 사이각
	vec2 base = vec2(1,0);										// 두벡터중 하나 (1,0) 기본벡터
	float temp = dot(k, base);									// 분자
	float magA = sqrt ( k.x * k.x + k.y * k.y );				// 분모 1
	float magB = sqrt ( base.x * base.x + base.y * base.y );	// 분모 2
	temp = temp / (magA * magB);								// temp는 cos(a) 값
	float angle = acos(temp);									// acos 을 통해서 angle을 구함


	// 시간이 특정일때 순차적으로 생성된다.
	if (u_Scale > a_Position.x)
	{
		float newTime = u_Scale - a_Position.x; // 파티클이 생성하고 난 뒤의 시간 ( 0 ~ 2sec )
		newTime = fract(newTime/2);				// 0~2사이로 계속 왔다갔다 하도록 만드는 방법 (시간은 계속 증가한다.)
												// fract(newTime/2)*2 에서 * 2 를 빼야 점 찍은데 까지만 날아간다.

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