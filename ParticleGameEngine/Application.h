#pragma once

#include <GLFW\glfw3.h>

class Application
{
public:
	Application(int screenWidth, int screenHeight);
	~Application();

	void Init();
	void Update(GLfloat deltaTime);
	void ProcessInput(GLFWwindow * window, GLfloat deltaTime);
	void Render();

private:
	int screenWidth, screenHeight;
};