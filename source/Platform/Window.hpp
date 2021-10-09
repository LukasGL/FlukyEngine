#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
namespace Fluky
{
	class World;
	/*
	* La clase Window provee una interfaz que permite al usario configurar y/o consultar informaci�n de la ventana de la aplicaci�n.
	*/
	class Window {
	public:
		friend class World;

		/*
		*
		*/
		bool ShouldClose() const noexcept;

		/*
		*
		*/
		glm::ivec2 GetWindowDimensions() const noexcept;

		/*
		*
		*/
		glm::ivec2 GetWindowFrameBufferSize() const noexcept;

		/*
		*
		*/
		void SetWindowDimensions(const glm::ivec2& dimensions) noexcept;

		GLFWwindow* GetHandle() const;

		int width, height;
		GLFWwindow* m_windowHandle;
	private:
		void StartUp() noexcept;
		void ShutDown() noexcept;
		void Update() noexcept;
	};
}
#endif