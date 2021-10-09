#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP
#include "../Platform/Window.hpp"
#include "../Platform/Input.hpp"
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

		Input& GetInput() noexcept;
		Window& GetWindow() noexcept;
		void EndApplication() noexcept;

	private:
		World(Application& app);
		~World();
		void StartMainLoop() noexcept;
		void Update(float timeStep) noexcept;

		Input m_input;
		Window m_window;
		Application& m_application;
		bool m_shouldClose;

	};



}
#endif