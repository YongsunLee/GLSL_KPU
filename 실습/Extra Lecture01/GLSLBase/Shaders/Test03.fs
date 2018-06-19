#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_TexPos;

uniform sampler2D u_Texture;

void main()
{
	vec2 newTexPos = v_TexPos;
	
	// y축 반전
	//newTexPos.y = 1 - newTexPos.y;

	// 1/4 출력
	//newTexPos.x = newTexPos.x / 2;
	//newTexPos.y = newTexPos.y / 2;

	// WARP 옵션 GL_REPAET
	//newTexPos.x = newTexPos.x * 2;
	//newTexPos.y = newTexPos.y * 2;
	
	// uniform 추가
	// 뒤의 곱셈 값 변경

	// 하얀색을 검은색으로 변경

	FragColor = texture(u_Texture, newTexPos);

	if (FragColor == vec4(1,1,1,1) )
		FragColor = vec4(0,0,0,1);
}
