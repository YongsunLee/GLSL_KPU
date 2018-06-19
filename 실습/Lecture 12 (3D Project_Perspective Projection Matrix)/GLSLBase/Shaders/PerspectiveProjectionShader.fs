#version 330

in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_Pos;

uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;

// weight
// 각 조명이 얼마만큼의 영향을 줄 것인지 정하는 것
const float c_Ambient = 0.2f;
const float c_Diffuse = 0.7f;
const float c_Specular = 0.5f;

out vec4 FragColor;

void main()
{
	// Normal 과 현재의 Light Direction이 필요하다.
	// Light Position에서 현재의 Postion을 빼면 된다.
	// v_Pos :: Surface의 반사되는 현재 위치 (World 좌표계)

	vec3 lightDir = normalize(u_LightPos - v_Pos);

	// 카메라의 Dircetion
	// 카메라에서 부터 현재 포지션을 빼면된다.;
	vec3 ViewDirc = normalize(u_CameraPos - v_Pos);
	
	vec3 reflectDir = reflect(-lightDir, v_Normal);

	float ambient = 1.0f;
	float diffuse = max(0, dot(lightDir, v_Normal));			// Camera의 위치와는 상관이 없는 것을 볼 수 있다.
	float specular = pow(max(0, dot(ViewDirc, reflectDir)), 128);	// 그냥 구하면 많이 퍼져있어서 Pow를 준다.
	
    FragColor.rgb = (c_Ambient * ambient + c_Diffuse * diffuse + c_Specular * specular) * v_Color.rgb;
	FragColor.a = v_Color.a;
}

/*

Phong Shading

Phong Lighting Model
ambient + diffuse + specular = result(Phong)

ambient :: 환경광
-> 반사된 빛들에 의해서 밝아지는 것을 의미 (const 형태의 값으로 더해주면 된다)

diffuse :: 난반사
-> 물체라는 것의 표면이 평평할 수 없다. (표면이 되게 거칠다.)
-> 그렇기 때문에 반사 되는 빛이 사방 팔방으로 균일하게 튀어 나오게 되는 것이 난반사이다.
-> 라이트의 Direction과 Surface의 Normal 만이 영향을 미친다.

 specular :: 정반사
 입사각과 반사각이 같은 것을 의미


*/