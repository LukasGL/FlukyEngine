#include "World.hpp"
#include <chrono>
namespace Fluky {

	World::World(Application& app) :
		//m_objectManager(),
		//m_eventManager(),
		m_window(),
		m_input(),
		m_application(app),
		m_shouldClose(false)
	{
		m_window.StartUp();
		m_input.StartUp();
		m_application = std::move(app);
		m_application.StartUp(*this);
	}

	World::~World() {
		m_application.UserShutDown(*this);
		m_window.ShutDown();
		m_input.ShutDown();

	}

	
	Input& World::GetInput() noexcept {
		return m_input;
	}

	Window& World::GetWindow() noexcept {
		return m_window;
	}

	void World::EndApplication() noexcept {
		m_shouldClose = true;
	}

	void World::StartMainLoop() noexcept {
		std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();

		while (!m_window.ShouldClose() && !m_shouldClose)
		{
			std::chrono::time_point<std::chrono::steady_clock> newTime = std::chrono::steady_clock::now();
			const auto frameTime = newTime - startTime;
			startTime = newTime;
			float timeStep = std::chrono::duration_cast<std::chrono::duration<float>>(frameTime).count();
			Update(timeStep);
		}

	}

	void World::Update(float timeStep) noexcept
	{
		m_input.Update();
		m_application.UserUpdate(*this, timeStep);
		m_window.Update();
	}
}
