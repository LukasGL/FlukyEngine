#include "Window.hpp"
#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#ifndef _WINDOWS_
#undef APIENTRY
#endif

namespace Fluky {
	static void GLFWErrorCallback(int error, const char* description)
	{
		fprintf(stderr, "GLFW error %d: %s\n", error, description);
	}
	void Window::StartUp() noexcept
	{
		const int success = glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		auto monitor = glfwGetPrimaryMonitor();
		m_windowHandle = glfwCreateWindow(1024, 768, "Fluky Engine", nullptr, nullptr);
		//m_windowHandle = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), fullScreen? monitor : NULL, NULL);
		if (!m_windowHandle)
			return;
		glfwMakeContextCurrent(m_windowHandle);
		// Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
		// Most graphics APIs must be used on the same thread that created the window.
		bgfx::renderFrame();
		// Initialize bgfx using the native window handle and window resolution.
		bgfx::Init init;
		init.platformData.nwh = glfwGetWin32Window(m_windowHandle);
		glfwGetWindowSize(m_windowHandle, &width, &height);
		init.resolution.width = (uint32_t)width;
		init.resolution.height = (uint32_t)height;
		init.resolution.reset = BGFX_RESET_VSYNC;
		if (!bgfx::init(init))
			return;
		const bgfx::ViewId kClearView = 0;
		bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
		bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	}
	void Window::ShutDown() noexcept
	{
		bgfx::shutdown();
		glfwDestroyWindow(m_windowHandle);
		//glfwTerminate();
	}
	void Window::Update() noexcept
	{
		glfwPollEvents();
		// Handle window resize.
		int oldWidth = width, oldHeight = height;
		glfwGetWindowSize(m_windowHandle, &width, &height);
		if (width != oldWidth || height != oldHeight) {
			bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
			//bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
		}
	}

	glm::ivec2 Window::GetWindowDimensions() const noexcept
	{
		int width, height;
		glfwGetWindowSize(m_windowHandle, &width, &height);
		return glm::ivec2(width,height);
	}
	glm::ivec2 Window::GetWindowFrameBufferSize() const noexcept
	{
		int width, height;
		glfwGetFramebufferSize(m_windowHandle, &width, &height);
		return glm::ivec2(width, height);
	}
	void Window::SetWindowDimensions(const glm::ivec2 &dimensions) noexcept
	{
		bgfx::reset((uint32_t)dimensions.x, (uint32_t)dimensions.y, BGFX_RESET_VSYNC);
		//bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	}
	GLFWwindow* Window::GetHandle() const {
		return m_windowHandle;
	}

	bool Window::ShouldClose() const noexcept
	{
		return glfwWindowShouldClose(m_windowHandle);
	}
	//class Window {
	//public:
	//	int width, height;
	//	

	//	bool ShouldClose() const noexcept
	//	{
	//		return glfwWindowShouldClose(m_windowHandle);
	//	}
	//	
	//	glm::ivec2 GetWindowDimensions() const noexcept
	//	{
	//		int width, height;
	//		glfwGetWindowSize(m_windowHandle, &width, &height);
	//		return glm::ivec2(width,height);
	//	}
	//	glm::ivec2 GetWindowFrameBufferSize() const noexcept
	//	{
	//		int width, height;
	//		glfwGetFramebufferSize(m_windowHandle, &width, &height);
	//		return glm::ivec2(width, height);
	//	}
	//	void SetWindowDimensions(const glm::ivec2 &dimensions) noexcept
	//	{
	//		bgfx::reset((uint32_t)dimensions.x, (uint32_t)dimensions.y, BGFX_RESET_VSYNC);
	//		//bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	//	}
	//	GLFWwindow* GetHandle() const {
	//		return m_windowHandle;
	//	}
	//private:
	//	GLFWwindow* m_windowHandle = nullptr;
	//	glm::ivec2 m_oldWindowPos = glm::vec2(0,0);
	//};
}