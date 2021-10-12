#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "../Platform/Window.hpp"
#include "../Platform/JoystickInput.hpp"
#include "../Rendering/Figures.hpp"
#include "../Audio/Audio.hpp"
#include "../Application.hpp"

#include <memory>
#include <array>
#include <filesystem>
#include <string>

namespace Fluky {

	class World {
	public:

		friend class Engine;

		World(const World& world) = delete;
		World& operator=(const World& world) = delete;

		JoystickInput& GetJoystickInput() noexcept;
		Window& GetWindow() noexcept;
		void EndApplication() noexcept;
		void CreateFigure() noexcept;

		void PlayWav(const char* file) noexcept;

	private:
		World(Application& app);
		~World();
		void StartMainLoop() noexcept;
		void Update(float timeStep) noexcept;

		Window m_window;
		JoystickInput m_joystickinput;
		Application& m_application;
		bool m_shouldClose;
		Audio m_audio;

		bool add_figure;

	};



}
#endif