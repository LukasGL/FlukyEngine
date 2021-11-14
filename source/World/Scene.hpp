#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include "entt/entt.hpp"

namespace Fluky {

	class Scene {
	public:
		friend class World;
		friend class GameObject;

		GameObject CreateGameObject();

		template<typename T>
		T AddComponent(GameObject gameObject);

		void ShutDownScene();

	protected:

		entt::registry* GetRegistry();

	private:


		entt::registry registry;
	};



}
#endif