#include "Window.hpp"
#define GLFW_INCLUDE_NONE

#include <iostream>
#include <stdio.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <imgui/imgui.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#ifndef _WINDOWS_
#undef APIENTRY
#endif

#include "InputComponent.hpp"

namespace Fluky {

	//Figures figtest;

	uint16_t m_numLights;
	bgfx::UniformHandle u_lightPosRadius;
	bgfx::UniformHandle u_lightRgbInnerR;

	static void GLFWErrorCallback(int error, const char* description)
	{
		fprintf(stderr, "GLFW error %d: %s\n", error, description);
	}
	void Window::StartUp() noexcept
	{
		const int success = glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);
		//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
#ifndef NDEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
		auto monitor = glfwGetPrimaryMonitor();
		m_windowHandle = glfwCreateWindow(1024, 768, "Fluky Engine", nullptr, nullptr);
		//m_windowHandle = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), fullScreen? monitor : NULL, NULL);
		if (!m_windowHandle)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
		}
		else
		{
			std::cout << "GLFW window created successfully!" << std::endl;
		}

		glfwMakeContextCurrent(m_windowHandle);

		joyInput.SetKeyCallback(m_windowHandle);

		joyInput.SetJoystickCallback();

		joyInput.pollJoysticks();


		// Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
		// Most graphics APIs must be used on the same thread that created the window.
		bgfx::renderFrame();


		debug = BGFX_DEBUG_NONE;
		reset = BGFX_RESET_VSYNC;

		// Initialize bgfx using the native window handle and window resolution.
		bgfx::Init init;
		init.platformData.nwh = glfwGetWin32Window(m_windowHandle);
		glfwGetWindowSize(m_windowHandle, &width, &height);
		init.type = bgfx::RendererType::WebGPU;
		init.resolution.width = (uint32_t)width;
		init.resolution.height = (uint32_t)height;
		init.resolution.reset = reset;
		if (!bgfx::init(init))
			return;
		// Enable debug text.
		bgfx::setDebug(debug);
		// Set view 0 clear state.
		/*bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
		);*/
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
		bgfx::setViewRect(0, 0, 0, width, height);


		m_numLights = 1;
		u_lightPosRadius = bgfx::createUniform("u_lightPosRadius", bgfx::UniformType::Vec4, m_numLights);
		u_lightRgbInnerR = bgfx::createUniform("u_lightRgbInnerR", bgfx::UniformType::Vec4, m_numLights);

		/*if (figtest.Init()) {
			std::cout << "Figures initialized succesfully!" << std::endl;
		}*/

	}
	void Window::ShutDown() noexcept
	{
		//figtest.~Figures();
		bgfx::shutdown();
		glfwDestroyWindow(m_windowHandle);
		//glfwTerminate();
	}
	void Window::Update() noexcept
	{

		glfwPollEvents();

		joyInput.pollJoysticks();

		// Handle window resize.
		/*int oldWidth = width, oldHeight = height;
		glfwGetWindowSize(m_windowHandle, &width, &height);
		const bgfx::ViewId kClearView = 0;
		bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
		if (width != oldWidth || height != oldHeight) {
			bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
			bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
		}*/

		// Set view 0 default viewport.
		//bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));

		//const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
		//const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };

		bx::Vec3 at = { 0.f,0.f,0.f };
		bx::Vec3 eye = { 0.f,0.f,0.f };

		if (cameraComponent) {
			//at = {cameraComponent->GetAtX(), cameraComponent->GetAtY(), cameraComponent->GetAtZ() };
			//eye = { cameraComponent->GetEyeX(), cameraComponent->GetEyeY(), cameraComponent->GetEyeZ() };
			at = { cameraComponent->GetAtX(),cameraComponent->GetAtY(),cameraComponent->GetAtZ() };
			eye = { cameraComponent->GetMtxX(), cameraComponent->GetMtxY(),   cameraComponent->GetMtxZ() };
		}
		else {
			at = { 0.0f, 0.0f,   0.0f };
			eye = { 0.0f, 0.0f, -5.0f };
		}
		// Set view and projection matrix for view 0.
		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(width) / float(height), 0.1f, 2000.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));
		}

		/*float lightPosRadius[4][(m_numLights==0)? 1: m_numLights];
		for (uint32_t ii = 0; ii < m_numLights; ++ii)
		{
			lightPosRadius[ii][0] = 2.0f;
			lightPosRadius[ii][1] = 20.0f;
			lightPosRadius[ii][2] = 2.0f;
			lightPosRadius[ii][3] = 100.0f;
		}*/

		bgfx::setUniform(u_lightPosRadius, &lightPoseRadius, m_numLights);

		bgfx::setUniform(u_lightRgbInnerR, &lightRgbInnerR, m_numLights);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

		//figtest.Update();

		// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
		bgfx::frame();

	}

	glm::ivec2 Window::GetWindowDimensions() const noexcept
	{
		int width, height;
		glfwGetWindowSize(m_windowHandle, &width, &height);
		return glm::ivec2(width, height);
	}
	glm::ivec2 Window::GetWindowFrameBufferSize() const noexcept
	{
		int width, height;
		glfwGetFramebufferSize(m_windowHandle, &width, &height);
		return glm::ivec2(width, height);
	}
	void Window::SetWindowDimensions(const glm::ivec2& dimensions) noexcept
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