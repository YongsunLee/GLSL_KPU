#version 330

// input

// 2번
in vec3 a_Position;

// 1번 3번
//in vec4 a_Position;

//in vec4 a_Color;

// output
// 1, 3번
//out float v_Value;

2번
out vec2 v_Value;

void main()
{
	// 1번
	//gl_Position = a_Position;
	//gl_Position.w = 1.0f;			// w값이 0이면 화면에 그려지지 않으므로 1.0으로 조정
	//
	//v_Value = a_Position.w;			
	// vs output 첫번째 vertex의 아웃풋은 0, 두번째 vertex의 아웃풋은 1
	// 0과 1이 넘어갔으므로 사이의 값은 보간이 되어 넘어간다.
	//

	// 2번
	gl_Position.xyz = a_Position;
	gl_Position.w = 1.0f;			// w값이 0이면 화면에 그려지지 않으므로 1.0으로 조정
	
	v_Value = a_Position.xy;

	// 3번
	//gl_Position = a_Position;
	//gl_Position.w = 1.0f;			// w값이 0이면 화면에 그려지지 않으므로 1.0으로 조정
	//
	//v_Value = a_Position.w;
}