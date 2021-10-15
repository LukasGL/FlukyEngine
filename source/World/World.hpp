#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "../Platform/Window.hpp"
#include "../Rendering/Figures.hpp"
#include "../Rendering/Text.hpp"
#include "../Audio/Audio.hpp"
#include "../Application.hpp"
#include "../Platform/JoystickInput.hpp"

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
		JoystickInput& GetJoystickInput() noexcept;

  /**
   * Returns the current window
	 * 
   * @return {Window}  : 
   */
		Window& GetWindow() noexcept;
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
		void Update(float timeStep) noexcept;

		// Current window
		Window m_window;
		// Current Joystick input instance
		JoystickInput m_joystickinput;
		// Current Application
		Application& m_application;
		// Audio instance
		Audio m_audio;

		// Should close world boolean
		bool m_shouldClose;
		// Render figure boolean
		bool add_figure;
		// Render text boolean
		bool add_text;

		bool playingwav;

	};



}
#endif