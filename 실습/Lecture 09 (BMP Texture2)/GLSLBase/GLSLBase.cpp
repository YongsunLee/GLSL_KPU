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

Renderer *g_Renderer = NULL;

float gTimer = 0.f;

void RenderScene(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	float centers[] = { 
		-0.5, -0.5,
		 0.5,  0.5,
		-0.45, -0.5,
		 0.5, -0.5 
	};

	/*
	전체 이미지 단위로 작동하는 것이기 때문에
	일반적인 Scene으로 사용하기는 조금 어렵다.

	그러나 정적인 화면이나 Scene에는 사용할만 하다.
	*/

	// Blend
	//float color[] = { 0.0f, 0.0f, 0.0f, 0.25f };
	//g_Renderer->DrawFillWindow(color);
	
	// Draw
	//g_Renderer->DrawRader(centers, gTimer);
	//g_Renderer->DrawSTParticle(0, 0, 1, 1, gTimer);
	//g_Renderer->DrawFAParticle(centers, gTimer);

	g_Renderer->DrawBlockTexture(10.f, 3.f);

	gTimer += 0.01f;

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();

	g_Renderer->SetMouseInput(x, y);
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
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

