#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void Test();

	// Lecture 02 실습
	void Lecture2();

	// Lecture 03 실습 
	void Lecture3();

	// Lecture 04 실습
	void Lecture4();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;

	// 실습 2
	GLuint m_Lecture2 = 0;
	
	// 실습 3
	GLuint m_Lecture3 = 0;
	GLuint m_Color = 0;
	GLfloat gTime = 0.f;
	GLfloat gTime2 = 0.f;

	// 실습 4
	GLuint m_Lecture4 = 0;
	GLuint m_Lecture4_1 = 0;
	GLuint m_Lecture4Color1 = 0;
	GLuint m_Lecture4Color2 = 0;
};

