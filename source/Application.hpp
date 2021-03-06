#pragma once
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
namespace Fluky {

	class Window;
	class Input;
	class World;


	/**
	 * Application class
	 */
	class Application {
	public:

		friend class World;

		/**
		 * Virtual function that the engine has to implement. This method is called during the start process of the engine.
		   *
		 * @param  {World} world :
		 */
		virtual void UserStartUp(World& world) noexcept = 0;

		/**
		   * Virtual function that the engine has to implement. This method is called during the end process of the engine.
		 *
		 * @param  {World} world :
		 */
		virtual void UserShutDown(World& world) noexcept = 0;

		/**
		   * Virtual function that the engine has to implement. This method is called at every iteration of the main loop, the user has to
		   * set all the logic of the game here.
		 *
		 * @param  {World} world    :
		 * @param  {float} timestep :
		 */
		virtual void UserUpdate(World& world, float timestep, float time)  noexcept = 0;

		virtual ~Application() = default;
	private:
		/**
		   * Executes the world start up.
		 *
		 * @param  {World} world :
		 */
		void StartUp(World& world) noexcept;

	};
}
#endif

