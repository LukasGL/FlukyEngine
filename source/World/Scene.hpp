#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include "entt/entt.hpp"

namespace Fluky {

	class Scene {
	public:
		friend class World;
		friend class GameObject;

		class GameObject CreateGameObject();

		//template<typename T>
		//T AddComponent(GameObject gameObject);

		void ShutDownScene();

		void StartUp();


	private:

		std::vector<GameObject> gameObjectVector;

		entt::registry registry;
	};



}
#endif