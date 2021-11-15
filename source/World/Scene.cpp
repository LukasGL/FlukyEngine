#include "Scene.hpp"
#include "GameObject.hpp"

namespace Fluky {

	GameObject Scene::CreateGameObject() {
		GameObject gameObject = { registry.create(), this };
		gameObjectVector.push_back(gameObject);
		return gameObject;
	}

	/*template<typename T>
	T& Scene::AddComponent(GameObject gameObject) {
		return gameObject.AddComponent<T>(&this);
	}*/

	void Scene::StartUp() {
		for (auto i = gameObjectVector.begin(); i != gameObjectVector.end(); ++i) {
			i->StartUp();
		}
	}

	void Scene::ShutDownScene()
	{
		auto view = registry.view<TransformComponent, BoxComponent>();
		registry.destroy(view.begin(), view.end());
	}


}