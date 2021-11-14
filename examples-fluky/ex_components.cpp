#include "FlukyEngine.hpp"

class EXWorld : public Fluky::Application {
public:
	EXWorld() = default;
	~EXWorld() = default;
	virtual void UserStartUp(Fluky::World& world) noexcept override {

		auto cube = world.CreateGameObject();
		auto& boxComponent = cube.AddComponent<Fluky::BoxComponent>();
		auto& transformComponent = cube.AddComponent<Fluky::TransformComponent>();
		transformComponent.SetTranslation(0.f, 0.f, 0.f);
		//auto boxComponent = world.AddComponent<Fluky::BoxComponent>(cube);
		//world.AddComponent<Fluky::BoxComponent>(cube);

	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			auto& transf = gameObjects.at(i).GetComponent<Fluky::TransformComponent>();
			transf.RotateXY(1.f + time, 1.f + time);
		}
	}
};

int main()
{
	EXWorld exworld;
	Fluky::Engine engine(exworld);
	engine.StartMainLoop();

}