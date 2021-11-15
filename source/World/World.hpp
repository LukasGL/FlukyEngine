#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "Scene.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "../Audio/AudioComponent.hpp"
#include "../Platform/Window.hpp"
#include "../Platform/InputComponent.hpp"
#include "../Rendering/BoxComponent.hpp"
#include "../Application.hpp"

#include <memory>
#include <array>
#include <filesystem>
#include <string>

namespace Fluky {

	/**
	 * Defines the world where the game has to be rendered
	 */
	class World {

	public:
		friend class Engine;

		World(const World& world) = delete;
		/**
		 * Ends the current application
		 */
		void EndApplication() noexcept;

		/**
		 * Render a figure in the world
		 */
		void CreateFigure() noexcept;

		/**
		 * Generates text in the world
		 */
		void CreateText() noexcept;

		/**
		 * Plays .wav file when the world starts
		   *
		 * @param  {char*} file :
		 */
		void PlayWav(const char* file) noexcept;

		/**
	   * Get the joystick input instance
		 *
	   * @return {JoystickInput}  :
	   */
		InputComponent& GetJoystickInput() noexcept;

		/**
		 * Returns the current window
		   *
		 * @return {Window}  :
		 */
		class Window& GetWindow() noexcept;

		/*template<typename T>
		T& AddComponent(class GameObject gameObject);*/

		GameObject CreateGameObject();

		std::vector<GameObject> GetGameObjects() {
			return scene.gameObjectVector;
		}

		void StartUpScene();

	private:
		World(Application& app);
		/**
		 * ~World
		   *
		   * Kill all the components of the world
		 *
		 */
		~World();
		/**
		 * Starts the main loop for this world
		 */
		void StartMainLoop() noexcept;
		/**
		 * Updates the world and all it's components
		   *
		 * @param  {float} timeStep :
		 */
		void Update(float time, float timeStep) noexcept;

		void ShutDown();

		// Current window
		Window m_window;
		// Current Joystick input instance
		InputComponent m_joystickinput;
		// Current Application
		Application& m_application;
		// Audio instance
		AudioComponent m_audio;

		// Should close world boolean
		bool m_shouldClose;
		// Render figure boolean
		bool add_figure;
		// Render text boolean
		bool add_text;

		bool playingwav;

		Scene scene;

	};
}
#endif