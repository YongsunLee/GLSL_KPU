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

	void DrawTest01();
	void DrawTest02();
	void DrawTest03();

	void MakeVBOByTest01();
	void MakeVBOByTest02();
	void MakeVBOByTest03();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;

	// Extra Lecutre 01
	// Draw Rect
	//Test 01
	GLuint m_VBOTest01 = 0;
	GLuint m_Test01Shader = 0;

	// Extra Lecture 02
	// Gray Scale
	//Test 02
	GLuint m_VBOTest02 = 0;
	GLuint m_Test02Shader = 0;

	// Extra Lecture 03
	GLuint m_VBOTest03 = 0;
	GLuint m_Test03Shader = 0;

	GLuint m_Tex_Smile = 0;

};

