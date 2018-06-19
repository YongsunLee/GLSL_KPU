#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"
#include "LoadPng.h"
#include "..\glm\glm.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\euler_angles.hpp"

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

	GLuint Renderer::CreatePngTexture(char * filePath);

	// API 제작
	void DrawSTParticle(float sx, float sy, float tx, float ty, float time);
	void DrawFAParticle(float* centers, float time);
	void DrawRader(float* centers, float time);
	void DrawFillWindow(float* v4Color);
	void DrawTexture();
	void DrawSmileTexture();
	void DrawMultiTexture();
	void DrawSingleTextureAnimation();
	void DrawBlockTexture(float repeat, float sheer);
	void DrawFaceSinCurvByVertexShader();
	void DrawParticleAnimaiton();

	// 3D Object
	void DrawCube();
	void DrawPerspectiveCube();

	void FATest();

	void RotateObject(float x, float y);

	void CubeVBO();
	void FAParticleVBO();
	void STParticleVBO();
	void RaiderVBO();
	void FillRectVBO();
	void TextrueVBO();
	void SmileTextureVBO();
	void MultiTextureVBO();
	void SingleTextureAniVBO();

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

	// shader
	GLuint m_SolidRectShader = 0;
	GLuint m_STParticleShader = 0;
	GLuint m_FAParticleShader = 0;
	GLuint m_RaderShader = 0;
	GLuint m_FillWindowShader = 0;
	GLuint m_TextureShader = 0;
	GLuint m_smileTextureShader = 0;
	GLuint m_MultiTextureShader = 0;
	GLuint m_SingleTextureAnimationShader = 0;
	GLuint m_BlockTextureShader = 0;
	GLuint m_FaceSinCurvByVertexShader;
	GLuint m_ParticleAnimaitonShader;

	GLuint m_CubeShader;
	GLuint m_PerspectiveCubeShader;
	
	// VBO
	GLuint m_VBORect = 0;
	GLuint m_VBOMovePoints = 0;
	GLuint m_VBORaderRect = 0;
	GLuint m_VBOFillRect = 0;
	GLuint m_VBOTexRect = 0;

	GLuint m_VBOPosTex = 0;
	GLuint m_VBOTexWLongRect = 0;

	GLuint m_VBOSinCurvFace = 0;
	GLuint m_nFaceVertex = 0;

	GLuint m_VBOParticleVertex = 0;
	GLuint m_nParticleCnt;

	GLuint m_VBOCube = 0;

	// Texture
	GLuint m_gTexture = 0;
	GLuint m_smileTexture = 0;

	GLuint glTexture0 = 0;
	GLuint glTexture1 = 0;
	GLuint glTexture2 = 0;
	GLuint glTexture3 = 0;
	GLuint glTexture4 = 0;
	GLuint glTexture5 = 0;
	GLuint gTextureIDTotal = 0;

	GLuint m_Tex_twice = 0;
	GLuint m_Tex_Test = 0;
	GLuint m_Tex_Block = 0;

	GLuint m_ParticleTextrue = 0;

	// Png
	GLuint m_pngTex_Particle = 0;

	// Timer
	GLfloat m_fTimer = 0;

	// Camera Position
	glm::vec3 m_v3Camera_Position;
	// Camera Look-at Position
	glm::vec3 m_v3Camera_Lookat;
	// Camera Up Vector
	glm::vec3 m_v3Camera_Up;

	// 절두체
	glm::mat4 m_m4OrthoProj;
	glm::mat4 m_m4PerspectiveProj;
	glm::mat4 m_m4View;			// Camera
	glm::mat4 m_m4ProjView;		// Projection * View
	glm::mat4 m_m4PerspectiveView;

	// Cube Object Vector (계속 변화될 값)
	glm::vec3 m_v3ModelTranslation;
	glm::vec3 m_v3ModelRotation;
	glm::vec3 m_v3ModelScaling;

	// Cube Object Matrix (Rendering 전에 한번씩 계산)
	glm::mat4 m_m4ModelTranslation;
	glm::mat4 m_m4ModelRotation;
	glm::mat4 m_m4ModelScaling;

	glm::mat4 m_m4Model;
};

