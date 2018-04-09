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
		-0.5, -0.5, 0.f, -0.5, 0.5, 0.f, 0.5, 0.5, 0.f, //Triangle1
		-0.5, -0.5, 0.f,  0.5, 0.5, 0.f, 0.5, -0.5, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
	
	// Lecture05
	float point[] = { -1.0, 0.0, 1.0f };
	
	glGenBuffers(1, &m_VBOPoint);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOPoint);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

	// �ǽ� 2 sin ���Ʒ��� �����̴� vertex
	int pointCount = 500;
	float *Points = new float[(pointCount + 1) * 4];
	for(int i = 0; i <= pointCount; ++i)
	{
		Points[i * 4 + 0] = (i / (float)pointCount) * 2 - 1;
		Points[i * 4 + 1] = 0;
		Points[i * 4 + 2] = 0;
		Points[i * 4 + 3] = 1.f;
	}
	glGenBuffers(1, &m_VBOPoints);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOPoints);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (pointCount + 1) * 4, Points, GL_STATIC_DRAW);

	// �ǽ� 3 ���� sin ������ ���� �����̴� vertex

	float *MovePoints = new float[(pointCount + 1) * 4];
	for (int i = 0; i <= pointCount; ++i)
	{
		MovePoints[i * 4 + 0] = ((float)i / (float)pointCount) * 2; // Make Timer
		MovePoints[i * 4 + 1] = (float)rand() / (float)RAND_MAX; // width
		MovePoints[i * 4 + 2] = (float)rand() / (float)RAND_MAX; // period
		MovePoints[i * 4 + 3] = 1.f;
		if ((float)rand() / (float)RAND_MAX > 0.5f) { MovePoints[i * 4 + 2] *= -1.f; };
	}
	glGenBuffers(1, &m_VBOMovePoints);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOMovePoints);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (pointCount + 1) * 4, MovePoints, GL_STATIC_DRAW);

}

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

//  Shader Ȯ��
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

void Renderer::Test()
{
	float newX, newY;

	// GLSL ���� ���� ����
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);

}

void Renderer::Lecture5()
{
	// Lecture 5_1
	
	glUseProgram(m_SolidRectShader);

	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOMovePoints);
	glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// uniform
	// DrawArray ���� �ҷ��� �Ѵ�.
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, m_fTimer);

	// -1 ~ 1 ����
	// Lecture 5���� Uniform ���� 1���� Ŀ���� ���� -1.f �� �����߱� ������
	// ó�� ���� 1�� �����ϸ� ���� -1�� ���� �Ǿ���.

	m_fTimer += 0.01f;
	// ���ǹ��� ����� ���� 1�� ���鼭 �������.
	// Vertex�� ������ �� x 0���� 2�� ���̿��� �߻��ϵ��� ����� ���� ���� 
	// 2�ʰ� ���� Vertex ���� 1.f ���� �Ѿ�� ȭ�鿡�� �������. 
	// �� ���� (3�ʰ� �Ǵ� ������ 1�ʰ� �Ǵ� �������� �����ϸ� �� �ݺ��ȴ�.)
	//if (m_fTimer > 1.f) m_fTimer = -1.f;

	glPointSize(2);

	glDrawArrays(GL_POINTS, 0, 500);
}

void Renderer::Lecture5InputVersion()
{
	// Lecutre 5�� (-1,0) ���� (1,0)���� Vertex�� ������ ���� sin��� ���� �̵��ϴ� ����̾���.
	// �� �������� ������ �Է¹޴� ������� ��������.

	// ���� �������� ����Ѵ�. (x,y) + k * t (���� + ���� * �ð�)
	// sin ��� �߾��� �ش� ������ �� ó�� ������ ��������� �Ѵ�. (������ �������� �Ѵ�.)
	// �� ���� ������ 0�̱� ������ �̵��ȴ�.

	// �� �Է��� ���� �ϱ� ���ؼ� ���콺 Input�� �̿�����.
	// (0,0) (500,500) �ȼ��� �簢���̴�.

	// �������� ȭ�� �߾�(0,0)���� �Ѵٰ� �ϰ�
	// �� ���� ���콺 Ŭ���� ����

	glUseProgram(m_SolidRectShader);

	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOMovePoints);
	glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// uniform
	// DrawArray ���� �ҷ��� �Ѵ�.
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, m_fTimer);

	GLuint StartPoint = glGetUniformLocation(m_SolidRectShader, "u_startPoint");
	glUniform2f(StartPoint, 0.0f, 0.0f);

	GLuint EndPoint = glGetUniformLocation(m_SolidRectShader, "u_endPoint");
	glUniform2f(EndPoint, m_targetPointX, m_targetPointY);
	
	// -1 ~ 1 ����
	// Lecture 5���� Uniform ���� 1���� Ŀ���� ���� -1.f �� �����߱� ������
	// ó�� ���� 1�� �����ϸ� ���� -1�� ���� �Ǿ���.

	m_fTimer += 0.01f;
	// ���ǹ��� ����� ���� 1�� ���鼭 �������.
	// Vertex�� ������ �� x 0���� 2�� ���̿��� �߻��ϵ��� ����� ���� ���� 
	// 2�ʰ� ���� Vertex ���� 1.f ���� �Ѿ�� ȭ�鿡�� �������. 
	// �� ���� (3�ʰ� �Ǵ� ������ 1�ʰ� �Ǵ� �������� �����ϸ� �� �ݺ��ȴ�.)
	//if (m_fTimer > 1.f) m_fTimer = -1.f;

	glPointSize(2);

	glDrawArrays(GL_POINTS, 0, 500);
	
}

void Renderer::SetTargetPoint(float x, float y)
{
	// �ȼ��� �¿� (-1, 1) ���� (1, -1) �� �簢������ ��������� �Ѵ�.
	// (-inputY + 250) / 250
	// ( inputX - 250) / 250

	m_targetPointX = ( x - 250.f) / 250.f; // -1, 1
	m_targetPointY = (-y + 250.f) / 250.f; // -1, 1

	std::cout << m_targetPointX << ", " << m_targetPointY << "\n";

}
