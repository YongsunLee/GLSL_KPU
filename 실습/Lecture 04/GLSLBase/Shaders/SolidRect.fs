#version 330

layout(location=0) out vec4 FragColor;

// 1번 3번
//in float v_Value;

// 2번
in vec2 v_Value;

uniform float u_Scale;
uniform float u_Size;

void main()
{
	// 첫번째 인풋은 0
	// 0~1사이의 값이 계속 넘어온다.
	//
	// Sin 곡선을 이용하기 위함 (0~1사이의 값)
	float PrintValue = (sin(u_Scale) + 1.0f) / 2.0f;
	float SizeValue = (sin(u_Size) + 1.0f) / 2.0f;
	
	// 1번
	// 그냥 u_Scale 값을 0~1사이의 값으로 넘겨주어도 된다.
	//
	//if (v_Value > PrintValue -0.1f && v_Value < PrintValue +0.1f)
	//	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	//else
	//	FragColor = vec4(0);

	// 2번
	// 원의 안쪽
	if ((v_Value.x * v_Value.x + v_Value.y * v_Value.y) > 0.25f || 
		(v_Value.x * v_Value.x + v_Value.y * v_Value.y) < 0.23f * SizeValue)
		FragColor = vec4(0);
	else	// 원의 바깥쪽
		FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f) * vec4(PrintValue,PrintValue,PrintValue, 1.0f);
	
	// 3번
	//if (v_Value > PrintValue -0.1f && v_Value < PrintValue + 0.1f)
	//	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	//else
	//	FragColor = vec4(0);

}
