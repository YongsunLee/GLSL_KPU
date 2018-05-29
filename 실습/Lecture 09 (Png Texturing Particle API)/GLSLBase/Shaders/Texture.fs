#version 330

uniform sampler2D uTexSampler;

in vec2 v_TexPos;

layout(location=0) out vec4 FragColor;

void main()
{
	//FragColor = vec4(v_TexPos.x, v_TexPos.y, 0.0f, 1.f);

	// 스위즐링 이라고 하는 것
	// r 채널에 b
	// g 채널에 g
	// b 채널에 r
	
	//vec4 t1 = texture(uTexSampler0, v_TexPos).bgra;
	//vec4 t2 = texture(uTexSampler1, v_TexPos).bgra;
	//
	//float newX = ;
	//float newY = ;
	//
	//if (sin(newX) > newY)
	//	FragColor = t1;
	//else
	//	FragColor = t2;
	//
	//float newnewY = v_TexPos.y * 3.141592 * 50 + u_Time;
	//float greyScale = sin(newnewY);
	//FragColor = FragColor * abs(vec4(pow(greyScale, 7)));
	
	FragColor = texture(uTexSampler, v_TexPos).bgra;
}
