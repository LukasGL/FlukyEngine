#include "Application.hpp"

namespace Fluky {
 /**
  * Application 
  * 
	* Starts the start up that is in the world
	*
  * @param  {world} undefined : 
  */
	void Application::StartUp(World& world) noexcept
	{
		UserStartUp(world);
	}
}