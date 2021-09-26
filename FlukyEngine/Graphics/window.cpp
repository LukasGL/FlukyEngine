#include "window.h"
#include <iostream>

namespace fluky { namespace graphics {

	bool Window::m_Keys[MAX_KEYS];
	bool Window::m_MouseButtons[MAX_BUTTONS];
	double Window::mx;
	double Window::my;

	void fluky::graphics::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void fluky::graphics::mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	Window::Window(const char* name, int width, int height)
	{
		m_Name = name;
		m_Width = width;
		m_Height = height;
		if (!init())
			glfwTerminate();

		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
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
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create GLFW window!" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		return true;
	}

	bool Window::isKeyPressed(unsigned int keycode)
	{
		if (keycode >= MAX_KEYS)
			return false;
		return m_Keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button)
	{
		if (button >= MAX_BUTTONS)
			return false;
		return m_MouseButtons[button];
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}
	void Window::update()
	{
		glfwSwapBuffers(m_Window);
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glViewport(0, 0, m_Width, m_Height);
		glfwPollEvents();
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}
} }