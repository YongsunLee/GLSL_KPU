#version 330

in vec2 v_TexPos;

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;

in float v_Alpha;

void main()
{
	FragColor = texture(u_Texture, v_TexPos);

	FragColor.a = FragColor.a * v_Alpha;
}
