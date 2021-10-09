#include "Input.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
namespace Fluky
{
	class Input::InputImplementation {
	public:
		InputImplementation() :m_windowHandle(nullptr), m_mouseWheelOffset(0.0, 0.0) {}
		InputImplementation(const InputImplementation& input) = delete;
		InputImplementation& operator=(const InputImplementation& input) = delete;
		void StartUp() noexcept {
			m_windowHandle = glfwGetCurrentContext();
			if (!m_windowHandle)
			{
				std::cout << "Unable to find window" << std::endl;
			}
			
		}

		void ShutDown() noexcept {

		}
		void Update() noexcept {
			m_mouseWheelOffset.x = 0.0;
			m_mouseWheelOffset.y = 0.0;
			glfwPollEvents();
		}
		/*void OnMouseScroll(const MouseScrollEvent& e)
		{
			m_mouseWheelOffset = glm::dvec2(e.xOffset, e.yOffset);
		}*/
		inline bool IsKeyPressed(int keycode) const noexcept
		{
			return glfwGetKey(m_windowHandle, keycode) == GLFW_PRESS;
		}
		inline bool IsMouseButtonPressed(int button) const noexcept {
			return glfwGetMouseButton(m_windowHandle, button) == GLFW_PRESS;
		}
		inline glm::dvec2 GetMousePosition() const noexcept {
			double x, y;
			glfwGetCursorPos(m_windowHandle, &x, &y);
			return glm::dvec2(x, y);
		}
		inline glm::dvec2 GetMouseWheelOffset() const noexcept {
			return m_mouseWheelOffset;
		}
		void SetCursorType(CursorType type) noexcept
		{
			switch (type)
			{
			case CursorType::Disabled:
			{
				glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				return;
			}
			case CursorType::Hidden:
			{
				glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				return;
			}
			case CursorType::Normal:
			{
				glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				return;
			}

			}
		}
	private:
		GLFWwindow* m_windowHandle;
		glm::dvec2 m_mouseWheelOffset;
	};

	Input::Input() : p_Impl(std::make_unique<InputImplementation>()) {}

	Input::~Input() = default;

	void Input::Update() noexcept
	{
		p_Impl->Update();
	}

	bool Input::IsKeyPressed(int keycode) const noexcept
	{
		return p_Impl->IsKeyPressed(keycode);
	}

	bool Input::IsMouseButtonPressed(int button) const noexcept
	{
		return p_Impl->IsMouseButtonPressed(button);
	}

	glm::dvec2 Input::GetMousePosition() const noexcept
	{
		return p_Impl->GetMousePosition();
	}

	glm::dvec2 Input::GetMouseWheelOffset() const noexcept
	{
		return p_Impl->GetMouseWheelOffset();
	}
	void Input::SetCursorType(CursorType type) noexcept
	{
		p_Impl->SetCursorType(type);
	}

	void Input::StartUp() noexcept {
		p_Impl->StartUp();
	}

	void Input::ShutDown() noexcept {
		p_Impl->ShutDown();
	}

}