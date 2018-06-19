/*
Copyright 2018 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

enum MouseInputSide {
	LEFT = 0,
	RIGHT = 2
};

enum MouseInputType {
	BUTTONDOWN = 0,
	BUTTONUP = 1
};

bool gl_mLButton = false;
bool gl_mRButton = false;
Renderer *g_Renderer = NULL;

float gTimer = 0.f;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.f);	// Depth�� Clear�Ҷ� � ������ Clear �ϴ°�?

	float centers[] = { 
		-0.5, -0.5,
		 0.5,  0.5,
		-0.45, -0.5,
		 0.5, -0.5 
	};

	/*
	��ü �̹��� ������ �۵��ϴ� ���̱� ������
	�Ϲ����� Scene���� ����ϱ�� ���� ��ƴ�.

	�׷��� ������ ȭ���̳� Scene���� ����Ҹ� �ϴ�.
	*/

	// Blend
	//float color[] = { 0.0f, 0.0f, 0.0f, 0.4f };
	//g_Renderer->DrawFillWindow(color);
	
	// Draw
	//g_Renderer->DrawRader(centers, gTimer);
	//g_Renderer->DrawSTParticle( 0 - (gTimer/ 50.f), 0 - (gTimer / 50.f), 1, 1, gTimer);
	//g_Renderer->DrawFAParticle(centers, gTimer);

	//g_Renderer->DrawBlockTexture(3, 2);
	
	//g_Renderer->DrawFaceSinCurvByVertexShader();
	
	//g_Renderer->DrawParticleAnimaiton();

	//g_Renderer->DrawCube();
	g_Renderer->DrawPerspectiveCube();

	gTimer += 0.0012f;

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gl_mLButton = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		gl_mLButton = false;
	}

	RenderScene();
}

// ���콺�� ��ġ
void MouseMove(int x, int y)
{
	if (gl_mLButton)
	{
	/*	gl_accX = (pervX - x) / 50.f;
		gl_accY = (pervY - y) / 50.f;

		PervX = x;
		PervY = y;*/
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();

	switch (key)
	{
	default:
		break;
	}
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("GLSL KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

