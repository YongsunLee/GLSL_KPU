#version 330

in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_Pos;

uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;

// weight
// �� ������ �󸶸�ŭ�� ������ �� ������ ���ϴ� ��
const float c_Ambient = 0.2f;
const float c_Diffuse = 0.7f;
const float c_Specular = 0.5f;

out vec4 FragColor;

void main()
{
	// Normal �� ������ Light Direction�� �ʿ��ϴ�.
	// Light Position���� ������ Postion�� ���� �ȴ�.
	// v_Pos :: Surface�� �ݻ�Ǵ� ���� ��ġ (World ��ǥ��)

	vec3 lightDir = normalize(u_LightPos - v_Pos);

	// ī�޶��� Dircetion
	// ī�޶󿡼� ���� ���� �������� ����ȴ�.;
	vec3 ViewDirc = normalize(u_CameraPos - v_Pos);
	
	vec3 reflectDir = reflect(-lightDir, v_Normal);

	float ambient = 1.0f;
	float diffuse = max(0, dot(lightDir, v_Normal));			// Camera�� ��ġ�ʹ� ����� ���� ���� �� �� �ִ�.
	float specular = pow(max(0, dot(ViewDirc, reflectDir)), 128);	// �׳� ���ϸ� ���� �����־ Pow�� �ش�.
	
    FragColor.rgb = (c_Ambient * ambient + c_Diffuse * diffuse + c_Specular * specular) * v_Color.rgb;
	FragColor.a = v_Color.a;
}

/*

Phong Shading

Phong Lighting Model
ambient + diffuse + specular = result(Phong)

ambient :: ȯ�汤
-> �ݻ�� ���鿡 ���ؼ� ������� ���� �ǹ� (const ������ ������ �����ָ� �ȴ�)

diffuse :: ���ݻ�
-> ��ü��� ���� ǥ���� ������ �� ����. (ǥ���� �ǰ� ��ĥ��.)
-> �׷��� ������ �ݻ� �Ǵ� ���� ��� �ȹ����� �����ϰ� Ƣ�� ������ �Ǵ� ���� ���ݻ��̴�.
-> ����Ʈ�� Direction�� Surface�� Normal ���� ������ ��ģ��.

 specular :: ���ݻ�
 �Ի簢�� �ݻ簢�� ���� ���� �ǹ�


*/