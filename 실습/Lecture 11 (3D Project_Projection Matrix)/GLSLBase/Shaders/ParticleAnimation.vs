#version 330

in vec3 a_Position;
in vec2 a_TexPos;
in vec4 Velocity;

uniform float u_Time;

out vec2 v_TexPos;

out float v_Alpha;

//const vec3 g_Gravity = vec3(0, -0.4, 0);	// y�� ���� �������� �߷�	
const vec3 g_Gravity = vec3(0, 0, -0.98);	// z�� ���� �������� �߷�

void main()
{
	float newTime = u_Time - Velocity.w;		// ���� �ð� - Start Time (��ƼŬ ���� �ٸ� �ð��� �ֱ� ���ؼ�)
	vec3 newPos = vec3(-100, -100, -100);

	float alpha = 0;

	if(newTime > 0){
		newTime = fract(newTime/0.5) * 0.5;

		alpha = 1-fract(newTime/0.5);			// fract ���� 1�� ����� ������ alpha�� 0�� ���������.

		newPos = 
		a_Position.xyz								// Base Position
		+ newTime * Velocity.xyz					// Velocity ����
		+ 0.5 * g_Gravity * pow(newTime, 2);		// acceleration
	}
	
	gl_Position = vec4(newPos, 1.f);

	v_Alpha = alpha;

	v_TexPos = a_TexPos;
}