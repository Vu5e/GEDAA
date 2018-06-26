#include <GLFW/glfw3.h>
#include<iostream>

void gameUpdate(float deltaTime)
{
	std::cout << "delta time : " << deltaTime << std::endl;
}

int main(void)
{
	GLFWwindow* window;

	/*Initialize the library*/
	if (!glfwInit())
	{
		return -1;
	}

	/*Create s windowed mode window and its OpenGL context*/

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/*Make the window's context current*/
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); //enable/disable vsync

						 /*Loop until the user closes the window*/
	while (!glfwWindowShouldClose(window))
	{
		/*Render here*/
		glClear(GL_COLOR_BUFFER_BIT);

		//==== calculate delta time & fps

		//,,,// glfwGetTime();
		//...
		float deltaTime = 100; //
		float fps = 60;
		//...
		// ..

		gameUpdate(deltaTime);

		//==================================

		/*Swap front and back buffers*/
		glfwSwapBuffers(window);

		/*Poll for and process events*/
		glfwPollEvents();
	}
}