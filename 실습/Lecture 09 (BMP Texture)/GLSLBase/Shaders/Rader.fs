#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Pos;

uniform float u_Time;
uniform vec2 u_CenterPosition[4];

const float pi = 3.141592;

void main()
{
	float weight = 0;

	for(int i = 0 ; i < 4; ++i){
		float distance = length(v_Pos - u_CenterPosition[i]);

		if (distance < 0.05f)
			weight += 0.3f;
	}

	float distance1 = length(v_Pos);
	float newTime = fract(u_Time/2) * 2;
	float finalColor = 0;

	if (distance1 > newTime - 0.02f && distance1 < newTime + 0.02f)
	{
		finalColor = 1 * weight + 0.2f;
	}
	else
	{
		discard;
	}
	FragColor = vec4(finalColor);
	
	//	FragColor = vec4(153.f/255.f, 1.f, 153.f/255.f, 1.f);
}

/*

Fragment Shader�� ȭ���� ���� ���� �ȴ�.
��, ClearBuffer�� �� �ʿ䰡 ����. (glClear) - GLSLBase.cpp - RenderScene Ȯ��

�׷��� �̹��� ��� ��Ǻ��� ����ϱ� ���ؼ��� �̹����� �����־�� �Ѵ�.
�׷��� discard�� ����Ѵ�.

Clear ��� Blend�� ����ؼ� ��Ǻ� ȿ���� �������� �����.

*/