#include "Application.hpp"

namespace Fluky {
	void Application::StartUp(World& world) noexcept
	{
		UserStartUp(world);
	}
}