#pragma once
#include "GLFW/glfw3.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class Window {
private:
	const char* name;
	int width, height;
	GLFWwindow* window;

	static bool keys[MAX_KEYS];
	static bool mouseButtons[MAX_BUTTONS];
	static double mx, my;
public:
	Window(const char* name, int width, int height);
	~Window();
	void update();
	bool closed() const;
	void clear() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

	static bool isKeyPressed(unsigned int keycode);
	static bool isMouseButtonPressed(unsigned int button);
private:
	bool init();
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};