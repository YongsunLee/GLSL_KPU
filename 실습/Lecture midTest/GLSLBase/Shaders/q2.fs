#version 330

layout(location=0) out vec4 FragColor;

const float pi = 3.141592;

in vec2 v_Pos;

void main()
{
	// 문제 6
	//float distacne = length(v_Pos); // 0 ~ 1
	//float greyScale = sin(distacne * pi * 4);
	//FragColor = vec4(greyScale);

	// 문제 7
	//float distance1 = length(v_Pos - vec2(-1,0));
	//float distance2 = length(v_Pos - vec2(1,0));

	//if (distance1 < 1.0f || distance2 < 1.0f)
	//	FragColor = vec4(1);
	//else
	//	FragColor = vec4(0);

	// 문제 8
	float distance1 = length(v_Pos - vec2(-1,0));
	float distance2 = length(v_Pos - vec2(1,0));
	float greyScale1 = clamp(-(floor(distance1) - 1), 0, 1);	// 0 ~ 1 사이의 값
	float greyScale2 = clamp(-(floor(distance2) - 1), 0, 1);	// 0 ~ 1 사이의 값

	/*

	floor(distacne)를 통해서 0, 1, 2 값이 나오는데
	여기서 -1 을 하면 -1 0 1 값이 등장
	여기서 이 전체를 -1을 하면 1 0 -1 로 변경되고
	이걸 clamp 해버리면
	1은 1값 0은 0값 -1은 0 값으로 clamp

	이걸 그대로 사용하면 1, 0 을 가진 색상이 된다.

	*/

	FragColor = vec4(greyScale1 + greyScale2);

}

