#include "World.hpp"

#include "TransformComponent.hpp"
#include "../Rendering/BoxComponent.hpp"
#include "GameObject.hpp"
#include "RegistryHandler.hpp"
#include <iostream>
#include <chrono>
#include <thread>
namespace Fluky {

	BoxComponent figures;
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
		playingwav = false;
		m_application = std::move(app);
		m_application.StartUp(*this);
	}
 
	World::~World() {
		m_application.UserShutDown(*this);
		if (add_figure) {
			figures.~BoxComponent();
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
			std::this_thread::sleep_until(newTime + std::chrono::seconds(1/60));
			const std::chrono::duration<float, std::milli> frameTime = newTime - startTime;
			startTime = newTime;
			float timeStep = std::chrono::duration_cast<std::chrono::duration<float>>(frameTime).count();
			if (frameTime > std::chrono::milliseconds(17)) {
				timeStep = 0.016f;
			}
			Update(timeStep);
		}
	}

	void World::Update(float timeStep) noexcept
	{
		//std::cout << timeStep * 1000.f << "ms" << std::endl;
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
					TransformComponent transform;
					transform.RotateXY(joystick.axes[1], joystick.axes[0]);
					figures.Update(transform);
					if (joystick.buttons[1]) {
						std::cout << "tecla" << std::endl;
						PlayWav("demo.wav");
					}
				}
				if (joystickId == GLFW_JOYSTICK_2)
				{
					TransformComponent transform;
					transform.RotateXY(joystick.axes[1], joystick.axes[0]);
					figures.Update(transform);
				}
			}
		}

		JoystickInput joyInput = m_window.GetJoystickHandler();
		JoystickContainer joysticks = joyInput.GetJoysticks();

		for (auto& elem : joysticks)
		{
			auto& joystickId = elem.first;
			auto& joystick = elem.second;

			float const buttonSize = 2.0f / joystick.buttons.size();

			if (!playingwav && joystick.buttons[0]) {
				PlayWav("demo.wav");
				playingwav = true;
			}
		}

		for (auto i = gameObjectVector.begin(); i != gameObjectVector.end(); ++i) {
			i->Update(registry.get()->registry);
		}

		m_window.Update();
	}


	GameObject World::CreateGameObject() {
		entt::registry * _registry = &registry.get()->registry;
		GameObject gameObject;
		gameObject.CreateGameObject(*_registry);
		gameObjectVector.push_back(gameObject);
		return gameObject;
	}

	template<typename T>
	T World::AddComponent(GameObject gameObject) {
		entt::registry * _registry = &registry.get()->registry;
		return gameObject.AddComponent<T>(*_registry);
	}

	void World::ShutDownRegistry()
	{
		entt::registry* _registry = &registry.get()->registry;
		auto view = (*_registry).view<TransformComponent, BoxComponent>();
		(*_registry).destroy(view.begin(), view.end());
	}

}
