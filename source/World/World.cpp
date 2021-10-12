#include "World.hpp"
#include <chrono>
namespace Fluky {

	Figures figures;

	World::World(Application& app) :
		//m_objectManager(),
		//m_eventManager(),
		m_window(),
		m_joystickinput(),
		m_application(app),
		m_shouldClose(false),
		m_audio()
	{
		m_audio.StartUp();
		m_window.StartUp();
		//m_input.StartUp();
		add_figure = false;
		m_application = std::move(app);
		m_application.StartUp(*this);
	}

	World::~World() {
		m_application.UserShutDown(*this);
		if (add_figure) {
			figures.~Figures();
		}
		m_audio.ShutDown();
		m_window.ShutDown();
		//m_input.ShutDown();

	}

	void World::CreateFigure() noexcept {
		figures.Init();
		add_figure = true;
	}

	void World::PlayWav(const char* file) noexcept {
		m_audio.Play("demo.wav");
	}



	JoystickInput& World::GetJoystickInput() noexcept {
		return m_joystickinput;
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
		m_application.UserUpdate(*this, timeStep);

		if (add_figure) {
			figures.Update();
		}
		m_window.Update();
	}
}
