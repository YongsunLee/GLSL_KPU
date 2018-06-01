#version 330

uniform sampler2D uTexSampler;

in vec2 v_TexPos;

layout(location=0) out vec4 FragColor;

void main()
{
	//FragColor = vec4(v_TexPos.x, v_TexPos.y, 0.0f, 1.f);

	vec2 newPos;

	newPos.x = fract(v_TexPos.x * 3);
	newPos.y = (2 - floor(v_TexPos.x * 3)) / 3.f + (v_TexPos.y / 3.f);

	FragColor = texture(uTexSampler, newPos);
}

/*

floor(v_TexPos.x * 2) 를 하면

화면 절반을 기준으로 0, 1 값을 가지게 되고
여기서 1에서 이 값을 빼주면

1, 0 이 된다.

이 값을 반으로 나누면 

0.5, 0 으로 시작점이 되고 여기에 증가량 0.5(원래의 v_TexPos.y (0 ~ 1)의 절반) 만큼 더해주면 된다. 

*/