#include "World.hpp"
#include <chrono>
namespace Fluky {

	Figures figures;
	Text m_text;

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
		add_text = false;
		m_application = std::move(app);
		m_application.StartUp(*this);
	}
 /**
  * Destructor of the world
	*
  */
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
		//m_input.ShutDown();

	}
 /**
  * World 
  * 
	* Generates text in the world
  */
	void World::CreateText() noexcept {
		m_text.Init();
		add_text = true;
	}
 /**
  * World 
  * 
	* Render a figure in the world
  */
	void World::CreateFigure() noexcept {
		figures.Init();
		add_figure = true;
	}
 
/**
 * World 
 * 
 * Plays .wav file when the world starts
 * 
 * @param  {file} undefined : 
 */
	void World::PlayWav(const char* file) noexcept {
		m_audio.Play(file);
	}


 /**
  * World 
  * 
	* Get the joystick input
	* 
  * @return {JoystickInput}  : 
  */
	JoystickInput& World::GetJoystickInput() noexcept {
		return m_joystickinput;
	}
 /**
  * World 
  * 
	* Get the current window
	* 
  * @return {Window}  : 
  */
	Window& World::GetWindow() noexcept {
		return m_window;
	}
 /**
  * World 
  * 
	* Ends the current application
	* 
  */
	void World::EndApplication() noexcept {
		m_shouldClose = true;
	}

 /**
	* World
	* 
	* Starts the main loop for this world 
	*
	*/
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
 /**
	* World
	* 
  * Updates the world
	* 
  */
	void World::Update(float timeStep) noexcept
	{
		m_application.UserUpdate(*this, timeStep);

		if (add_figure) {
			figures.Update();
		}
		m_window.Update();
	}
}
