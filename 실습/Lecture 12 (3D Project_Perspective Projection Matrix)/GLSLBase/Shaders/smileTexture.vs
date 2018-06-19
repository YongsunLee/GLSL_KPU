#version 330

in vec3 a_Position;
in vec2 a_uvPosition;

out vec2 v_TexPos;

void main()
{
	gl_Position = vec4(a_Position, 1.f);

	v_TexPos = a_uvPosition;
}