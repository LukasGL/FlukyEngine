#include "Scene.hpp"
#include "GameObject.hpp"

namespace Fluky {

	GameObject Scene::CreateGameObject() {
		GameObject gameObject = { registry.create(), this };
		gameObjectVector.push_back(gameObject);
		return gameObject;
	}



	void Scene::StartUp() {
		audioManager.StartUp();
		/*for (auto i = gameObjectVector.begin(); i != gameObjectVector.end(); ++i) {
			i->StartUp(*this);
		}*/

		auto view = registry.view<BoxComponent>();

		for (auto entity : view)
		{
			auto& box = view.get<BoxComponent>(entity);

			box.Init();
		}

		auto view3 = registry.view<AudioComponent>();

		for (auto entity : view3)
		{
			auto& audio = view3.get<AudioComponent>(entity);

			audio.StartUp(*this);
		}
	}

	void Scene::ShutDownScene()
	{
		auto view = registry.view<TransformComponent, BoxComponent>();
		registry.destroy(view.begin(), view.end());
	}


}