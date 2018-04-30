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


	unsigned char * loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight)
	{
		printf("Reading image %s\n", imagepath);
		outWidth = -1;
		outHeight = -1;
		// Data read from the header of the BMP file
		unsigned char header[54];
		unsigned int dataPos;
		unsigned int imageSize;
		// Actual RGB data
		unsigned char * data;

		// Open the file
		FILE * file = NULL;
		fopen_s(&file, imagepath, "rb");
		if (!file)
		{
			printf("Image could not be opened\n");
			return NULL;
		}

		if (fread(header, 1, 54, file) != 54)
		{
			printf("Not a correct BMP file\n");
			return NULL;
		}

		if (header[0] != 'B' || header[1] != 'M')
		{
			printf("Not a correct BMP file\n");
			return NULL;
		}

		if (*(int*)&(header[0x1E]) != 0)
		{
			printf("Not a correct BMP file\n");
			return NULL;
		}

		if (*(int*)&(header[0x1C]) != 24)
		{
			printf("Not a correct BMP file\n");
			return NULL;
		}

		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		outWidth = *(int*)&(header[0x12]);
		outHeight = *(int*)&(header[0x16]);

		if (imageSize == 0)
			imageSize = outWidth * outHeight * 3;

		if (dataPos == 0)
			dataPos = 54;

		data = new unsigned char[imageSize];

		fread(data, 1, imageSize, file);

		fclose(file);

		return data;
	}

	// API ¡¶¿€
	void DrawSTParticle(float sx, float sy, float tx, float ty, float time);
	void DrawFAParticle(float* centers, float time);
	void DrawRader(float* centers, float time);
	void DrawFillWindow(float* v4Color);
	void DrawTexture();

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
	GLuint m_FAParticleShader = 0;
	GLuint m_RaderShader = 0;
	GLuint m_FillWindowShader = 0;
	GLuint m_TextureShader = 0;

	GLuint m_VBORect = 0;
	GLuint m_VBOMovePoints = 0;
	GLuint m_VBORaderRect = 0;
	GLuint m_VBOFillRect = 0;

	GLuint m_VBOTexRect = 0;
	GLuint m_gTexture = 0;

	GLfloat m_fTimer = 0;
};

