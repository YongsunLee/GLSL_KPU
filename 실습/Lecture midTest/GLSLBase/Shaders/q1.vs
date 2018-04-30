#version 330

uniform float u_Time;

in vec3 a_Position;
in float a_Info;

void main()
{
	// 문제 2
	// 가운데에 점 찍기
	//gl_Position = vec4(a_Position, 1);
	
	// 문제 3
	// 반지름 0.5f 인 원의 궤도로 돌아라
	//gl_Position = vec4(sin(u_Time) * 0.5f, cos(u_Time) * 0.5f, 0, 1);

	// 문제 4
	// 주기 3개 짜리 Sin 곡선 그리기 시작점이 -Pi 부분으로 시작
	//float newX = fract(u_Time) * 2 - 1;	// -1 ~ 1사이
	//float newY = sin(newX * 3.141592f * 3);
	//gl_Position = vec4(newX, newY, 0, 1);

	// 문제 5
	// 점 두개가 다른 주기(0~4PI)로 이동하는 것 + 폭이 다른 것
	float newX = fract(u_Time) * 2 - 1;	// -1 ~ 1사이 (fract * 2 하면 0 ~ 2 사이의 값)
	float newY = sin((newX + 1) * 2 * 3.141592f) * a_Info;
	gl_Position = vec4(newX, newY, 0, 1);

}
