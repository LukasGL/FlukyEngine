#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "World/World.hpp"
#include "Application.hpp"
#include <memory>
namespace Fluky {
	class Engine
	{
	public:
		Engine(Application& app) : m_world(app) {}
		~Engine() = default;
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		/*
		* Starts the main loop of the engine
		*/
		void StartMainLoop() noexcept {
			m_world.StartMainLoop();
		}
	private:
		World m_world;
	};
}

#endif