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

	// 실습 2 sin 위아래로 움직이는 vertex
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

	// 실습 3 직접 sin 라인을 따라서 움직이는 vertex

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
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void Renderer::Test()
{
	float newX, newY;

	// GLSL 강좌 들어가면 설명
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
	// DrawArray 전에 불려야 한다.
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, m_fTimer);

	// -1 ~ 1 사이
	// Lecture 5에서 Uniform 값을 1보다 커지는 순간 -1.f 로 변경했기 때문에
	// 처음 값이 1에 도달하면 전부 -1로 변경 되었다.

	m_fTimer += 0.01f;
	// 조건문을 지우면 전부 1로 가면서 사라진다.
	// Vertex를 생성할 때 x 0에서 2초 사이에만 발생하도록 만들어 놨기 때문 
	// 2초가 지난 Vertex 들은 1.f 값을 넘어가서 화면에서 사라진다. 
	// 이 값을 (3초가 되는 순간을 1초가 되는 순간으로 변경하면 또 반복된다.)
	//if (m_fTimer > 1.f) m_fTimer = -1.f;

	glPointSize(2);

	glDrawArrays(GL_POINTS, 0, 500);
}

void Renderer::Lecture5InputVersion()
{
	// Lecutre 5는 (-1,0) 에서 (1,0)으로 Vertex가 난수에 따라서 sin곡선을 따라 이동하는 방식이었다.
	// 이 시작점과 끝점을 입력받는 방식으로 변경하자.

	// 선의 방정식을 사용한다. (x,y) + k * t (원점 + 기울기 * 시간)
	// sin 곡선의 중앙이 해당 직선인 것 처럼 수직을 변경해줘야 한다. (원점이 더해져야 한다.)
	// 즉 현재 기준이 0이기 때문에 이동된다.

	// 점 입력을 쉽게 하기 위해서 마우스 Input을 이용하자.
	// (0,0) (500,500) 픽셀의 사각형이다.

	// 시작점은 화면 중앙(0,0)으로 한다고 하고
	// 끝 점을 마우스 클릭을 받자

	glUseProgram(m_SolidRectShader);

	GLint posId = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(posId);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOMovePoints);
	glVertexAttribPointer(posId, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// uniform
	// DrawArray 전에 불려야 한다.
	GLuint id = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(id, m_fTimer);

	GLuint StartPoint = glGetUniformLocation(m_SolidRectShader, "u_startPoint");
	glUniform2f(StartPoint, 0.0f, 0.0f);

	GLuint EndPoint = glGetUniformLocation(m_SolidRectShader, "u_endPoint");
	glUniform2f(EndPoint, m_targetPointX, m_targetPointY);
	
	// -1 ~ 1 사이
	// Lecture 5에서 Uniform 값을 1보다 커지는 순간 -1.f 로 변경했기 때문에
	// 처음 값이 1에 도달하면 전부 -1로 변경 되었다.

	m_fTimer += 0.01f;
	// 조건문을 지우면 전부 1로 가면서 사라진다.
	// Vertex를 생성할 때 x 0에서 2초 사이에만 발생하도록 만들어 놨기 때문 
	// 2초가 지난 Vertex 들은 1.f 값을 넘어가서 화면에서 사라진다. 
	// 이 값을 (3초가 되는 순간을 1초가 되는 순간으로 변경하면 또 반복된다.)
	//if (m_fTimer > 1.f) m_fTimer = -1.f;

	glPointSize(2);

	glDrawArrays(GL_POINTS, 0, 500);
	
}

void Renderer::SetTargetPoint(float x, float y)
{
	// 픽셀을 좌우 (-1, 1) 상하 (1, -1) 의 사각형으로 변경해줘야 한다.
	// (-inputY + 250) / 250
	// ( inputX - 250) / 250

	m_targetPointX = ( x - 250.f) / 250.f; // -1, 1
	m_targetPointY = (-y + 250.f) / 250.f; // -1, 1

	std::cout << m_targetPointX << ", " << m_targetPointY << "\n";

}
