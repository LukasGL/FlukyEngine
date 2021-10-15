#include "World.hpp"
#include <chrono>
namespace Fluky {

	Figures figures;
	Text m_text;

	World::World(Application& app) :
		m_window(),
		//m_joystickinput(),
		m_application(app),
		m_shouldClose(false),
		m_audio()
	{
		m_audio.StartUp();
		m_window.StartUp();
		add_figure = false;
		add_text = false;
		m_application = std::move(app);
		m_application.StartUp(*this);
	}
 
	World::~World() {
		m_application.UserShutDown(*this);
		if (add_figure) {
			figures.~Figures();
		}
		if (add_text) {
			m_text.~Text();
		}
		m_audio.ShutDown();
		m_window.ShutDown();
	}
 
	void World::CreateText() noexcept {
		m_text.Init();
		add_text = true;
	}

	void World::CreateFigure() noexcept {
		figures.Init();
		add_figure = true;
	}
 
	void World::PlayWav(const char* file) noexcept {
		m_audio.Play(file);
	}

	/*JoystickInput& World::GetJoystickInput() noexcept {
		return m_joystickinput;
	}*/

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
			JoystickInput joyInput = m_window.GetJoystickHandler();
			JoystickContainer joysticks = joyInput.GetJoysticks();

			for (auto& elem : joysticks)
			{
				auto& joystickId = elem.first;
				auto& joystick = elem.second;

				float const buttonSize = 2.0f / joystick.buttons.size();

				if (joystickId == GLFW_JOYSTICK_1)
				{
					figures.Update(joystick.axes[1], joystick.axes[0]);
				}
				if (joystickId == GLFW_JOYSTICK_2)
				{
					figures.Update(joystick.axes[1], joystick.axes[0]);
				}
			}
		}
		m_window.Update();
	}
}
