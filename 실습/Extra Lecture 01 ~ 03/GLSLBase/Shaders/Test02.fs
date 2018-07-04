#version 330

layout(location=0) out vec4 FragColor;

in float v_Grey;
in vec2 v_Position;

void main()
{
	// Grey Sclae �ǽ�
//	FragColor = vec4(v_Grey, v_Grey, v_Grey, 1);
	
	// ������ ���� �׸��� �ǽ�
//	if (v_Grey > 0.5)
//		FragColor = vec4(1, 0, 0, 1);
//	else 
//		FragColor = vec4(0, 0, 0, 1);

//	Grey ������ ���� �簢��
//	float newGrey = floor(v_Grey * 2);
//	FragColor = vec4(newGrey, 0, 0, 1);
	
	// x ��ǥ�� ���� �簢��
//	float newGrey = floor(v_Position.x + 1);
//	FragColor = vec4(newGrey, 0, 0, 1);

	// y ��ǥ�� �Ʒ��� �簢��
//	float newGrey = floor(1-v_Position.y * 2);
//	FragColor = vec4(newGrey, 0, 0, 1);

	// �ﰢ��
//	if (v_Position.y - v_Position.x <= 0)
//		FragColor = vec4(1, 0, 0, 1);
//	else 
//		FragColor = vec4(0, 0, 0, 1);

	// ��
//	if((v_Position.y * v_Position.y) + (v_Position.x * v_Position.x) <= 0.25)
//		FragColor = vec4(1, 0, 0, 1);
//	else 
//		FragColor = vec4(0, 0, 0, 1);
//
	// ���Ͼ��ϰ� �����ϴ� ���� �ƴ� �ܰ躰 �����ϴ� ��
	// Floor
	float newGrey = floor(v_Grey * 4) / 3;
	FragColor = vec4(newGrey, newGrey, newGrey, 1);
}
