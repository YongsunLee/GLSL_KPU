#version 330

in vec3 a_Position;
in float a_Grey;

out float v_Grey;
out vec2 v_Position;

void main()
{
	gl_Position = vec4(a_Position, 1);

	v_Grey = a_Grey;
	v_Position = a_Position.xy;
}
