#pragma once
#ifndef REGISTRYHANDLER_HPP
#define REGISTRYHANDLER_HPP

#include "entt/entt.hpp"

namespace Fluky {

	class Registry {
	public:
		friend class World;
	private:
		entt::registry registry;
	};



}
#endif