#include "Scene.hpp"
#include "GameObject.hpp"

namespace Fluky {

	GameObject Scene::CreateGameObject() {
		GameObject gameObject;
		gameObject.CreateGameObject(registry);
		return gameObject;
	}

	template<typename T>
	T Scene::AddComponent(GameObject gameObject) {
		return gameObject.AddComponent<T>(registry);
	}

	void Scene::ShutDownScene()
	{
		auto view = registry.view<TransformComponent, BoxComponent>();
		registry.destroy(view.begin(), view.end());
	}

	entt::registry* Scene::GetRegistry() {
		return &registry;
	}

}