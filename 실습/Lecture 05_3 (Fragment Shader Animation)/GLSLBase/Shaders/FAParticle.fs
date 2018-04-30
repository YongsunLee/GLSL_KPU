#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Pos;

uniform float u_Time;
uniform vec2 u_CenterPosition[4];

const float pi = 3.141592;

void main()
{
	
	FragColor = vec4(0);

	// API 만들기
	// 임의의 지점에서 퍼져나가는 원 그리기
	for(int i = 0; i < 4; ++i){
		vec2 pos = v_Pos;
		vec2 center = u_CenterPosition[i];

		float distance = length(pos - center) * 2 * pi;	// 현재 좌표와 0,0 사이의 거리를 구하는 식
		
		FragColor += vec4(sin(distance * 8.f - u_Time) * clamp(1-distance/(2*pi), 0, 1));
	}


	// 원 그리기
	/*
	float x = v_Pos.x;
	float y = v_Pos.y;
	float r = 1.f;
	
	if ( (x*x + y*y) == r*r || (x*x + y*y) < r*r && (x*x + y*y) > 0.9f)
		FragColor = vec4(1.f, 1.f, 0.f, 1.f);
	else
		FragColor = vec4(0.f, 0.f, 0.f, 1);
	*/

	// Sin 곡선
	// 현재 x 값의 범위가 -1 ~ 1이므로 +1 * pi를 해서 0 ~ 2pi 주기로 변경해 준후
	// sin(x)를 하게 되면 해당 x 값을 알 수 있다.
	/*
	x = (x + 1) * pi;
	float sinx = sin(x + u_Time) * 0.5f;
	
	if ( sinx + 0.05 > y  && sinx - 0.05 < y)
		FragColor = vec4(1.f, 1.f, 0.f, 1.f);
	else 
		FragColor = vec4(0.f, 0.f, 0.f, 1);
	*/
	
	// Gray Color 확인하기
	/*
	float sinx = pow (abs(sin(x * pi * 4)), 1);	// pow를 하면 얇아진다.
	float siny = pow (abs(sin(y * pi * 4)), 1);
	FragColor = vec4(siny, siny, siny, 1);
	*/
}

/*

Fragment Shader에서는 해당 픽셀을 이동할 수 없다. (Frame Buffer 상에 고정되어 있는 값)
이미 결정된 값이다. 즉, Color 값을 변경 할 수만 있다. 
옮기고 싶으면 Vertex Shader에서 해야 한다.

Fragment Shader는 2D 이다.

*/