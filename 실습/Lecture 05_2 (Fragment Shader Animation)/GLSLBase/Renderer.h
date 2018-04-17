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

	// API ¡¶¿€
	void DrawSTParticle(float sx, float sy, float tx, float ty, float time);
	void DrawFAParticle(float* centers, float time);


	void FATest();

	void SetMouseInput(float x, float y);

	float m_targetPointX, m_targetPointY;
	float inputStack[8]{0};
	int InputCounter = 0;

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_SolidRectShader = 0;
	GLuint m_STParticleShader = 0;
	GLuint m_FAtestShader = 0;

	GLuint m_VBORect = 0;
	GLuint m_VBOMovePoints = 0;

	GLfloat m_fTimer = 0;
};

