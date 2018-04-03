#version 330

// input
//in vec3 a_Position;

//ДыБо
in vec4 a_Position;

in vec4 a_Color;

out vec4 v_Color;

void main()
{
	gl_Position = vec4(a_Position.rgb, 1);

	v_Color = a_Color;
}