#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D uTexSampler;

void main()
{
	vec4 t1 = texture(uTexSampler, gl_PointCoord);

	FragColor = t1;
}
