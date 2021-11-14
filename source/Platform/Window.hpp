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
	class InputComponent;
	/*
	* this class allow to the user create a window where render the game
	*/
	class Window {
	public:
		friend class World;
		friend class BoxComponent;

		/**
		 * What to do when the window closes
		 *
		 */
		bool ShouldClose() const noexcept;
		/**
		 * Returns the window dimensions
		   *
		 * @return {glm::ivec2}  :
		 */
		glm::ivec2 GetWindowDimensions() const noexcept;


		/**
		 * Returns window frame buffer size
		   *
		 * @return {glm::ivec2}  :
		 */
		glm::ivec2 GetWindowFrameBufferSize() const noexcept;
		/**
		 * Sets window dimensions
		   *
		 * @param  {glm::ivec2} dimensions :
		 */
		void SetWindowDimensions(const glm::ivec2& dimensions) noexcept;
		/**
		 * Returns the window handle
		   *
		 * @return {GLFWwindow*}  :
		 */
		GLFWwindow* GetHandle() const;
		InputComponent GetJoystickHandler();

		int width, height, debug, reset;
		GLFWwindow* m_windowHandle;
	private:
		/**
		   * what to do when the window starts up
		 *
		 */
		void StartUp() noexcept;
		/**
		   * what to do when the window shuts down
		 *
		 */
		void ShutDown() noexcept;
		/**
		 * what to do when the window updates
		   *
		 */
		void Update() noexcept;
	};

}
#endif