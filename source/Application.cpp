// FlukyEngine.cpp : Defines the entry point for the application.
//

#include "GLFW/glfw3.h"
#include <iostream>
#include "Graphics/window.h"

int main()
{

	Window window("Fluky!", 800, 600);

	glClearColor(0.1f, 0.2f, 0.3f, 0.1f);

	while (!window.closed())
	{
		window.clear();
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "A" << std::endl;
		}

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		window.update();
	}

	system("PAUSE");
	return 0;
	//if (!glfwInit()) {
	//	std::cerr << "glfw initialization failed" << std::endl;
	//	return -1;
	//}

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OPNEGL 3.3
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	//GLFWwindow* window = glfwCreateWindow(1280, 720, "Fluky Engine", nullptr, nullptr);

	//if (window == nullptr) {
	//	std::cerr << "GLFW window creation failed." << std::endl;
	//	glfwTerminate();
	//	return -2;
	//}

	//glfwMakeContextCurrent(window);

	////glClearColor(0.3f, 0.3f, 0.4f, 1.0f);

	//while (!glfwWindowShouldClose(window)) {
	//	glfwPollEvents();

	//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	glfwSwapBuffers(window);
	//}

	//glfwDestroyWindow(window);
	//glfwTerminate();

	//return 0;
}


