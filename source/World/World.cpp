#include "World.hpp"

#include <iostream>
#include <chrono>
#include <thread>
namespace Fluky {

	BoxComponent figures;

	World::World(Application& app) :
		//m_joystickinput(),
		m_application(app),
		m_shouldClose(false),
		m_window(),
		m_audio()
	{
		m_window.StartUp();
		playingwav = false;
		m_application = std::move(app);
		m_application.StartUp(*this);
		m_physicsSystem.InitPhysics();
	}

	World::~World() {
		m_application.UserShutDown(*this);
		if (add_figure) {
			figures.~BoxComponent();
		}
		m_window.ShutDown();
	}


	InputComponent& World::GetJoystickInput() noexcept
	{
		return m_window.joyInput;
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
		std::chrono::time_point<std::chrono::steady_clock> initialTime = std::chrono::steady_clock::now();


		while (!m_window.ShouldClose() && !m_shouldClose)
		{
			std::chrono::time_point<std::chrono::steady_clock> newTime = std::chrono::steady_clock::now();
			std::this_thread::sleep_until(newTime + std::chrono::seconds(1 / 60));
			const std::chrono::duration<float, std::milli> frameTime = newTime - startTime;
			startTime = newTime;
			float timeStep = std::chrono::duration_cast<std::chrono::duration<float>>(frameTime).count();
			if (frameTime > std::chrono::milliseconds(17)) {
				timeStep = 0.016f;
			}
			const std::chrono::duration<float, std::milli> timeChrono = newTime - initialTime;
			float time = std::chrono::duration_cast<std::chrono::duration<float>>(timeChrono).count();
			Update(time, timeStep);
		}
	}

	void World::Update(float time, float timeStep) noexcept
	{
		//std::cout << timeStep * 1000.f << "ms" << std::endl;
		m_application.UserUpdate(*this, timeStep, time);
		/*if (add_figure) {
			InputComponent joyInput = m_window.GetJoystickHandler();
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

		InputComponent joyInput = m_window.GetJoystickHandler();
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
		}*/

		/*InputComponent joyInput = m_window.joyInput;
		JoystickContainer joysticks = joyInput.GetJoysticks();

		for (auto& elem : joysticks)
		{
			auto& joystickId = elem.first;
			auto& joystick = elem.second;

			float const buttonSize = 2.0f / joystick.buttons.size();

			if (joystickId == 0)
			{
				std::cout << joystick.axes[0] << std::endl;
			}
		}*/

		for (auto i = scene.gameObjectVector.begin(); i != scene.gameObjectVector.end(); ++i) {
			i->Update(m_window);
		}

		m_physicsSystem.Update(timeStep);

		m_window.Update();
	}


	GameObject World::CreateGameObject() {
		return scene.CreateGameObject();
	}

	/*template<typename T>
	T& World::AddComponent(GameObject gameObject) {
		return gameObject.AddComponent<T>();
	}*/

	void World::StartUpScene() {
		scene.StartUp();
	}

	void World::ShutDown()
	{
		scene.ShutDownScene();
	}

	void World::ShutDownGameObject(GameObject gO) {


		gO.ShutDown();

		for (auto i = scene.gameObjectVector.begin(); i != scene.gameObjectVector.end(); ++i) {
			scene.gameObjectVector.erase(std::remove_if(scene.gameObjectVector.begin(), scene.gameObjectVector.end(), 
				[&gO](GameObject g)
				{ return g.equal(gO); }
			)
				, scene.gameObjectVector.end());
			if (scene.gameObjectVector.empty()) { break; }
		}

		//for (auto i = scene.gameObjectVector.begin(); i != scene.gameObjectVector.end(); ++i) {
		//	scene.gameObjectVector.erase(std::remove_if(scene.gameObjectVector.begin(), scene.gameObjectVector.end(),
		//		i->equal(gO)));
		//}


	}

}
