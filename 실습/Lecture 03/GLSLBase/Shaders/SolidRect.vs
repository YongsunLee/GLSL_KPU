#version 330

// input
in vec4 a_Position;
in vec4 a_Color;

// uniform
uniform float u_Scale;

// output
out vec4 v_Color;

void main()
{
	gl_Position = a_Position * vec4(u_Scale,u_Scale,u_Scale, 1.0);

	v_Color = a_Color;
}