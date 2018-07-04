#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D uTexSampler;

in float v_Color;
in vec2 v_TexPos;

void main()
{
	//FragColor = vec4(v_Color);

	FragColor = texture(uTexSampler, v_TexPos).bgra;
}
