#version 330

uniform sampler2D uTexSampler;

in vec2 v_TexPos;

layout(location=0) out vec4 FragColor;

void main()
{
	//FragColor = vec4(v_TexPos.x, v_TexPos.y, 0.0f, 1.f);

	FragColor = texture(uTexSampler, v_TexPos);
}

/*

FragColor = texture(uTexSampler, fract(v_TexPos * 3));

뒤에 fract를 넣어주면 glTexParameteri 에서 GL_REAPEAT를 한것과 같은 효과가 나온다.

*/