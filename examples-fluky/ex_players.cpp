#include "FlukyEngine.hpp"
#include <iostream>

class EXWorld : public Fluky::Application {
public:
	EXWorld() = default;
	~EXWorld() = default;
	virtual void UserStartUp(Fluky::World& world) noexcept override {

		auto cube = world.CreateGameObject();
		auto& boxComponent = cube.AddComponent<Fluky::BoxComponent>();
		auto& transformComponent = cube.AddComponent<Fluky::TransformComponent>();
		transformComponent.RotateXYZ(0.f, 0.f, 0.f);
		transformComponent.SetTranslation(0.f, 0.f, 0.f);
		auto& playerComponent = cube.AddComponent<Fluky::PlayerComponent>();
		playerComponent.SetPlayerId(&world.GetJoystickInput(), 0);

	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			auto& player = gameObjects.at(i).GetComponent<Fluky::PlayerComponent>();
			player.SetPlayerId(&world.GetJoystickInput(), 0);
			auto& transf = gameObjects.at(i).GetComponent<Fluky::TransformComponent>();
			transf.RotateXY(1.f + player.GetAxes()[1], 1.f + player.GetAxes()[0]);
			//player.GetAxes();
		}

		//world.GetJoystickInput();
	}
};

int main()
{
	EXWorld exworld;
	Fluky::Engine engine(exworld);
	engine.StartMainLoop();

}