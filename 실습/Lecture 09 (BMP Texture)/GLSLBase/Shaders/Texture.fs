#version 330

uniform sampler2D uTexSampler;
uniform sampler2D uTexSampler1;

uniform float u_Time;

in vec2 v_TexPos;

layout(location=0) out vec4 FragColor;

void main()
{
	//FragColor = vec4(v_TexPos.x, v_TexPos.y, 0.0f, 1.f);

	// ������ �̶�� �ϴ� ��
	// r ä�ο� b
	// g ä�ο� g
	// b ä�ο� r
	
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
	
	float tX = fract(v_TexPos.x * 10);
	float tY = fract(v_TexPos.y * 10);
	vec4 t1 = texture(uTexSampler, vec2(tx, ty)).bgra;
	FragColor = t1;
}

/*

FragColor = texture(uTexSampler, fract(v_TexPos * 3));

�ڿ� fract�� �־��ָ� glTexParameteri ���� GL_REAPEAT�� �ѰͰ� ���� ȿ���� ���´�.

*/