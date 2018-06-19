#version 330

layout(location=0) out vec4 FragColor;

in float v_Grey;
in vec2 v_Position;

void main()
{
	// Grey Sclae 실습
//	FragColor = vec4(v_Grey, v_Grey, v_Grey, 1);
	
	// 오른쪽 반쪽 그리기 실습
//	if (v_Grey > 0.5)
//		FragColor = vec4(1, 0, 0, 1);
//	else 
//		FragColor = vec4(0, 0, 0, 1);

//	Grey 값으로 우측 사각형
//	float newGrey = floor(v_Grey * 2);
//	FragColor = vec4(newGrey, 0, 0, 1);
	
	// x 좌표로 우측 사각형
//	float newGrey = floor(v_Position.x + 1);
//	FragColor = vec4(newGrey, 0, 0, 1);

	// y 좌표로 아래쪽 사각형
//	float newGrey = floor(1-v_Position.y * 2);
//	FragColor = vec4(newGrey, 0, 0, 1);

	// 삼각형
//	if (v_Position.y - v_Position.x <= 0)
//		FragColor = vec4(1, 0, 0, 1);
//	else 
//		FragColor = vec4(0, 0, 0, 1);

	// 원
//	if((v_Position.y * v_Position.y) + (v_Position.x * v_Position.x) <= 0.25)
//		FragColor = vec4(1, 0, 0, 1);
//	else 
//		FragColor = vec4(0, 0, 0, 1);
//
	// 리니어하게 증가하는 것이 아닌 단계별 증가하는 값
	// Floor
	float newGrey = floor(v_Grey * 4) / 3;
	FragColor = vec4(newGrey, newGrey, newGrey, 1);
}
