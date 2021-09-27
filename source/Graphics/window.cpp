#include "window.h"
#include <iostream>

bool Window::keys[MAX_KEYS];
bool Window::mouseButtons[MAX_BUTTONS];
double Window::mx;
double Window::my;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Window::Window(const char* name, int width, int height)
{
	this->name = name;
	this->width = width;
	this->height = height;
	if (!init())
		glfwTerminate();

	for (int i = 0; i < MAX_KEYS; i++)
	{
		keys[i] = false;
	}

	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		mouseButtons[i] = false;
	}
}

Window::~Window()
{
	glfwTerminate();
}


bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW window!" << std::endl;
		return false;
	}
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	return true;
}

bool Window::isKeyPressed(unsigned int keycode)
{
	if (keycode >= MAX_KEYS)
		return false;
	return keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button)
{
	if (button >= MAX_BUTTONS)
		return false;
	return mouseButtons[button];
}

void Window::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::closed() const
{
	return glfwWindowShouldClose(window) == 1;
}
void Window::update()
{
	glfwSwapBuffers(window);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwPollEvents();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->mouseButtons[button] = action != GLFW_RELEASE;
}