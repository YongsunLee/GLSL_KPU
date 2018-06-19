#version 330

in vec3 a_Position;
in vec2 a_TexPos;
in vec4 Velocity;

uniform float u_Time;

out vec2 v_TexPos;

out float v_Alpha;

//const vec3 g_Gravity = vec3(0, -0.4, 0);	// y축 으로 떨어지는 중력	
const vec3 g_Gravity = vec3(0, 0, -0.98);	// z축 으로 떨어지는 중력

void main()
{
	float newTime = u_Time - Velocity.w;		// 현재 시간 - Start Time (파티클 별로 다른 시간을 주기 위해서)
	vec3 newPos = vec3(-100, -100, -100);

	float alpha = 0;

	if(newTime > 0){
		newTime = fract(newTime/0.5) * 0.5;

		alpha = 1-fract(newTime/0.5);			// fract 값이 1에 가까워 질수록 alpha는 0에 가까워진다.

		newPos = 
		a_Position.xyz								// Base Position
		+ newTime * Velocity.xyz					// Velocity 적용
		+ 0.5 * g_Gravity * pow(newTime, 2);		// acceleration
	}
	
	gl_Position = vec4(newPos, 1.f);

	v_Alpha = alpha;

	v_TexPos = a_TexPos;
}