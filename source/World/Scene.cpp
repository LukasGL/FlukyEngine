#include "Scene.hpp"
#include "GameObject.hpp"

namespace Fluky {

	GameObject Scene::CreateGameObject() {
		GameObject gameObject = { registry.create(), this };
		return gameObject;
	}

	/*template<typename T>
	T& Scene::AddComponent(GameObject gameObject) {
		return gameObject.AddComponent<T>(&this);
	}*/

	void Scene::ShutDownScene()
	{
		auto view = registry.view<TransformComponent, BoxComponent>();
		registry.destroy(view.begin(), view.end());
	}


}