#include "FlukyEngine.hpp"
#include <iostream>

class EXWorld : public Fluky::Application {
public:
	EXWorld() = default;
	~EXWorld() = default;
	virtual void UserStartUp(Fluky::World& world) noexcept override {

		auto cube = world.CreateGameObject();
		auto& boxComponent = cube.AddComponent<Fluky::BoxComponent>();
		boxComponent.RotateXYZ(1.f, 1.f, 1.f);
		boxComponent.SetPosition(1.5f, 1.5f, 0.f);

		auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		boxComponent2.RotateXYZ(1.f, 1.f, 1.f);
		boxComponent2.SetPosition(-1.5f, 1.5f, 0.f);

		auto cube3 = world.CreateGameObject();
		auto& boxComponent3 = cube3.AddComponent<Fluky::BoxComponent>();
		boxComponent3.RotateXYZ(1.f, 1.f, 1.f);
		boxComponent3.SetPosition(-1.5f, -1.5f, 0.f);

		world.StartUpScene();

	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			auto& box = gameObjects.at(i).GetComponent<Fluky::BoxComponent>();
			box.RotateXY(1.f + time, 1.f + time);
		}
	}
};

int main()
{
	EXWorld exworld;
	Fluky::Engine engine(exworld);
	engine.StartMainLoop();

}