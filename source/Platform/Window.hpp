#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "InputComponent.hpp"
#include "CameraComponent.hpp"

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

		void SetMainCamera(CameraComponent& cam) {
			cameraComponent = &cam;
		}
		
		InputComponent joyInput;

		int width, height, debug, reset;
		GLFWwindow* m_windowHandle;

		CameraComponent* cameraComponent;

		void SetLightPos(Fluky::Vec3 pos) {
			lightPoseRadius[0] = pos.x;
			lightPoseRadius[1] = pos.y;
			lightPoseRadius[2] = pos.z;
		}

		void SetLightRadius(float rad) {
			lightPoseRadius[3] = rad;
		}

		void SetLightRGBA(float r, float g, float b, float a) {
			lightRgbInnerR[0] = r;
			lightRgbInnerR[1] = g;
			lightRgbInnerR[2] = b;
			lightRgbInnerR[3] = a;
		}

		
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

		float lightPoseRadius[4] = { 2.f,20.f,2.f,100.f };
		float lightRgbInnerR[4] = { 1.0f, 1.0f, 1.0f, 0.8f };
	};

}
#endif