#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "../Platform/Window.hpp"
#include "../Platform/JoystickInput.hpp"
#include "../Rendering/Figures.hpp"
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

	private:
		World(Application& app);
		~World();
		void StartMainLoop() noexcept;
		void Update(float timeStep) noexcept;

		Window m_window;
		JoystickInput m_joystickinput;
		Application& m_application;
		bool m_shouldClose;

		bool add_figure;

	};



}
#endif