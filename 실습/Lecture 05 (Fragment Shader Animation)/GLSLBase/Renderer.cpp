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
	m_STParticleShader = CompileShaders("./Shaders/STParticle.vs", "./Shaders/STParticle.fs");
	m_FAtestShader = CompileShaders("./Shaders/FATest.vs", "./Shaders/FATest.fs");

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
		-1.f, -1.f, 0.f, -1.f, 1.f, 0.f, 1.f,  1.f, 0.f, //Triangle1
		-1.f, -1.f, 0.f,  1.f, 1.f, 0.f, 1.f, -1.f, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
	
	// STP API
	int pointCount = 500;
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
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// Attach 이후에 지워져도 되는 오브젝트 이므로 지역변수 ShaderObj이다.
	// ShaderProgram 에 attach!!
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

//  Shader 확인
GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	// ReadFile
	// filename 받아서 string으로 변환해주는 것

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
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
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.\n";

	return ShaderProgram;
}

void Renderer::Test()
{
	// GLSL 강좌 들어가면 설명
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);

}

// API 함수
void Renderer::DrawSTParticle(float sx, float sy, float tx, float ty, float time)
{
	GLuint shader = m_STParticleShader;
	glUseProgram(shader);

	GLint posId = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOMovePoints);
	glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// uniform
	// DrawArray 전에 불려야 한다.
	GLuint id = glGetUniformLocation(shader, "u_Time");
	glUniform1f(id, time);

	GLuint StartPoint = glGetUniformLocation(shader, "u_startPoint");
	glUniform2f(StartPoint, sx, sy);

	GLuint EndPoint = glGetUniformLocation(shader, "u_endPoint");
	glUniform2f(EndPoint, tx, ty);
	
	glPointSize(2);

	glDrawArrays(GL_POINTS, 0, 500);
}

void Renderer::DrawFAParticle(float* centers, float time)
{
	GLuint shader = m_FAtestShader;
	glUseProgram(shader);

	GLint posId = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(posId, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	GLuint id = glGetUniformLocation(shader, "u_Time");
	glUniform1f(id, time);

	GLuint CenterPoisitionId = glGetUniformLocation(shader, "u_CenterPosition");
	glUniform2fv(CenterPoisitionId, 4, centers);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::FATest()
{
	GLuint shader = m_FAtestShader;
	glUseProgram(shader);

	GLint posId = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(posId, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	GLuint id = glGetUniformLocation(shader, "u_Time");
	glUniform1f(id, m_fTimer);
	m_fTimer += 0.05f;

	GLuint CenterPoisitionId = glGetUniformLocation(shader, "u_CenterPosition");
	//glUniform2f(CenterPoisitionId, m_targetPointX, m_targetPointY);
	glUniform2fv(CenterPoisitionId, 4, inputStack);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::SetMouseInput(float x, float y)
{
	m_targetPointX = (x - 250.f) / 250.f;
	m_targetPointY = (-y + 250.f) / 250.f;

	if (InputCounter < 4 ) {
		inputStack[InputCounter] = m_targetPointX;
		inputStack[InputCounter + 1] = m_targetPointY;
		InputCounter += 1;
	}
	else if (InputCounter >= 4) InputCounter = 0;
	

	//std::cout << m_targetPointX << ", " << m_targetPointY << std::endl;
}

