#version 330

layout(location=0) out vec4 FragColor;

uniform vec4 u_FillColor;

void main()
{
	FragColor = u_FillColor;
}
