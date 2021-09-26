#pragma once

#include <GLFW/glfw3.h>

namespace fluky {
	namespace graphics {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

		class Window
		{
		private:
			const char* m_Name;
			int m_Width, m_Height;
			GLFWwindow* m_Window;

			static bool m_Keys[MAX_KEYS];
			static bool m_MouseButtons[MAX_BUTTONS];
			static double mx, my;
		public:
			Window(const char* name, int width, int height);
			~Window();
			void update();
			bool closed() const;
			void clear() const;

			inline int getWidth() const { return m_Width; }
			inline int getHeight() const { return m_Height; }

			static bool isKeyPressed(unsigned int keycode);
			static bool isMouseButtonPressed(unsigned int button);
		private:
			bool init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		};
	}
}