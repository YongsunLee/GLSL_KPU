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

	// Lecture 02 실습 18.03.12. 삼각형 그려보기
	float vertices2[]
		= { 0.0f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f };

	glGenBuffers(1, &m_Lecture2);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	// 여기까지

	// Lecture 03 실습 
	float vertices3[]
		= { 0.0f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.8f, 0.0f, 1.0f };

	glGenBuffers(1, &m_Lecture3);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	// 색상 (Vertex 별로)
	float color3[] = { 1.f, 1.f, 0.f, 1.f, 
					  0.f, 1.f, 1.f, 1.f, 
					  1.f, 0.f, 1.f, 1.f };
	glGenBuffers(1, &m_Color);
	glBindBuffer(GL_ARRAY_BUFFER, m_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color3), color3, GL_STATIC_DRAW);
	// 여기까지

	// Lecture 04 실습
	/*
		다른 Array를 만들어서 사용하는 것이 아니라
		어차피 w 값은 1로 줄것이므로 (Shader 내부에서 1로 값을 줘버리고)
		Fragment에서 사용할 만한 데이터 (인덱스 값을 보낸다.)
		1번 버텍스는 0이고 2번 버텍스는 1이라는 값
	*/
	float vertices4[]
		= { -0.5, 0.0f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f, 1.0f };

	glGenBuffers(1, &m_Lecture4);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

	// 색상
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

//Shader 생성 함수
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
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}
// End

// 출력용 함수 & 수업 진행 함수
void Renderer::Test()
{
	float newX, newY;

	// GLSL 강좌 들어가면 설명
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	{
		glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	/*
	// Lecture02 실습 추가 코드
	// 내가 추가한거 수업은 Lecture2 함수에
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	// 여기까지
	*/

	glDisableVertexAttribArray(attribPosition);

}

void Renderer::Lecture2()
{
	glUseProgram(m_SolidRectShader);

	glEnableVertexAttribArray(0);
	
	// Lecture02 실습 추가 코드
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	// 여기까지

	//glDisableVertexAttribArray(0);
}

void Renderer::Lecture3()
{
	glUseProgram(m_SolidRectShader);
	
	// Lecture03 실습 추가 코드
	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture3);
	{
		glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	// 쉐이더 색상 추가
	GLint ColorId = glGetAttribLocation(m_SolidRectShader, "a_Color");
	glEnableVertexAttribArray(ColorId);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_Color);
	{
		glVertexAttribPointer(ColorId, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	// uniform
	// DrawArray 전에 불려야 한다.
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, gTime);
	gTime += 0.01;

	if (gTime > 1.f) gTime = 0.f;

	glDrawArrays(GL_TRIANGLES, 0, 3);
	// 여기까지


	//교수님 코드
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

	// Lecture04 실습 추가 코드
	// 1번 일정 간격의 선을따라 이동하는 모양
	/*
	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4);
	glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// uniform
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, gTime);

	gTime += 0.05f;

	// DrawArray 전에 모두 불려야 한다.
	glDrawArrays(GL_LINES, 0, 2);
	*/

	// 2번 사각형 넘겨서 원 그리기
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

	// 3번
	/*
	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4_1);
	glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// uniform
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, gTime);

	gTime += 0.05f;

	// DrawArray 전에 모두 불려야 한다.
	glDrawArrays(GL_LINES, 0, 8);
	*/

}
// End