#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	
	//Create VBOs
	CreateVertexBufferObjects();

	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{
	float rect[]
		=
	{
		-0.5, -0.5, 0.f, // v1
		-0.5,  0.5, 0.f, // v2
		 0.5,  0.5, 0.f, // v3
		-0.5, -0.5, 0.f, 
		 0.5,  0.5, 0.f, 
		 0.5, -0.5, 0.f, // v4
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	// Lecture 02 �ǽ� 18.03.12. �ﰢ�� �׷�����
	float vertices2[]
		= { 0.0f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f };

	glGenBuffers(1, &m_Lecture2);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	// �������

	// Lecture 03 �ǽ� 
	float vertices3[]
		= { 0.0f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.8f, 0.0f, 1.0f };

	glGenBuffers(1, &m_Lecture3);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	// ���� (Vertex ����)
	float color3[] = { 1.f, 1.f, 0.f, 1.f, 
					  0.f, 1.f, 1.f, 1.f, 
					  1.f, 0.f, 1.f, 1.f };
	glGenBuffers(1, &m_Color);
	glBindBuffer(GL_ARRAY_BUFFER, m_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color3), color3, GL_STATIC_DRAW);
	// �������

	// Lecture 04 �ǽ�
	/*
		�ٸ� Array�� ���� ����ϴ� ���� �ƴ϶�
		������ w ���� 1�� �ٰ��̹Ƿ� (Shader ���ο��� 1�� ���� �������)
		Fragment���� ����� ���� ������ (�ε��� ���� ������.)
		1�� ���ؽ��� 0�̰� 2�� ���ؽ��� 1�̶�� ��
	*/
	float vertices4[]
		= { -0.5, 0.0f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f, 1.0f };

	glGenBuffers(1, &m_Lecture4);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

	// ����
	float color4_1[] 
		= { 1.f, 1.f, 0.f, 1.f };
	glGenBuffers(1, &m_Lecture4Color1);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4Color1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color4_1), color4_1, GL_STATIC_DRAW);

	float color4_2[]
		= { 0.f, 0.f, 0.f, 1.f };
	glGenBuffers(1, &m_Lecture4Color2);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4Color2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color4_2), color4_2, GL_STATIC_DRAW);

	float vertices4_1[]
		= { -0.6f,  0.0f, 0.0f, 0.0f,
			-0.3f,  0.3f, 0.0f, 0.4f, 
			 0.3f, -0.3f, 0.0f, 0.6f,
			 0.6f,  0.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &m_Lecture4_1);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4_1), vertices4_1, GL_STATIC_DRAW);
}

//Shader ���� �Լ�
void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// Attach ���Ŀ� �������� �Ǵ� ������Ʈ �̹Ƿ� �������� ShaderObj�̴�.
	// ShaderProgram �� attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	// ReadFile
	// filename �޾Ƽ� string���� ��ȯ���ִ� ��

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}
// End

// ��¿� �Լ� & ���� ���� �Լ�
void Renderer::Test()
{
	float newX, newY;

	// GLSL ���� ���� ����
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	{
		glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	/*
	// Lecture02 �ǽ� �߰� �ڵ�
	// ���� �߰��Ѱ� ������ Lecture2 �Լ���
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	// �������
	*/

	glDisableVertexAttribArray(attribPosition);

}

void Renderer::Lecture2()
{
	glUseProgram(m_SolidRectShader);

	glEnableVertexAttribArray(0);
	
	// Lecture02 �ǽ� �߰� �ڵ�
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	// �������

	//glDisableVertexAttribArray(0);
}

void Renderer::Lecture3()
{
	glUseProgram(m_SolidRectShader);
	
	// Lecture03 �ǽ� �߰� �ڵ�
	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture3);
	{
		glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	// ���̴� ���� �߰�
	GLint ColorId = glGetAttribLocation(m_SolidRectShader, "a_Color");
	glEnableVertexAttribArray(ColorId);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_Color);
	{
		glVertexAttribPointer(ColorId, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	// uniform
	// DrawArray ���� �ҷ��� �Ѵ�.
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, gTime);
	gTime += 0.01;

	if (gTime > 1.f) gTime = 0.f;

	glDrawArrays(GL_TRIANGLES, 0, 3);
	// �������


	//������ �ڵ�
	/*
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture3);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_Color);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	*/

	//glDisableVertexAttribArray(0);
}

void Renderer::Lecture4()
{
	glUseProgram(m_SolidRectShader);

	// Lecture04 �ǽ� �߰� �ڵ�
	// 1�� ���� ������ �������� �̵��ϴ� ���
	/*
	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4);
	glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// uniform
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, gTime);

	gTime += 0.05f;

	// DrawArray ���� ��� �ҷ��� �Ѵ�.
	glDrawArrays(GL_LINES, 0, 2);
	*/

	// 2�� �簢�� �Ѱܼ� �� �׸���
	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(posId, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// uniform
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, gTime);

	GLuint id1 = glGetUniformLocation(m_SolidRectShader, "u_Size");
	glUniform1f(id1, gTime2);

	gTime += 0.05f;
	gTime2 -= 0.05f;

	glDrawArrays(GL_TRIANGLES, 0, 6);

	// 3��
	/*
	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4_1);
	glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// uniform
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, gTime);

	gTime += 0.05f;

	// DrawArray ���� ��� �ҷ��� �Ѵ�.
	glDrawArrays(GL_LINES, 0, 8);
	*/

}
// End