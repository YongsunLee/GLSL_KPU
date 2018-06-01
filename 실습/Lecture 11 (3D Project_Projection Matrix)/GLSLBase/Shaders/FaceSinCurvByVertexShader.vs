#version 330

in vec3 a_Position;

uniform float u_Time;
uniform mat4 u_ProjView;

out float v_Color;
out vec2 v_TexPos;

void main()
{
	vec3 newPos;

	newPos = a_Position;

	newPos.z = (sin(u_Time + ((a_Position.x + 0.5) * 2 * 3.141592)) * 0.5f) + a_Position.z;

		// Hold Sin
	//newPos.y = (sin(((a_Position.x + 0.5) * 2 * 3.141592)) * 0.5f) + a_Position.y;	// - a_Position.y 를 하면 뒤집힌다.
		
	// Animation Sin
	//newPos.y = (sin(u_Time + ((a_Position.x + 0.5) * 2 * 3.141592)) * 0.2f) + a_Position.y;	// - a_Position.y 를 하면 뒤집힌다.
	
	gl_Position = u_ProjView * vec4(newPos.xyz, 1.f);

	//v_Color = (1 + sin(u_Time + ((a_Position.x + 0.5) * 2 * 3.141592))) / 2;
	v_TexPos = a_Position.xy + vec2(0.5, 0.5);	// 0 ~ 1
}

/*

u_Time 을 Sin 내부에서 더해주면 Animation이 된다.


*/