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
		transformComponent.SetTranslation(1.5f, 0.f, 0.f);
		auto& playerComponent = cube.AddComponent<Fluky::PlayerComponent>();
		playerComponent.SetPlayerId(&world.GetJoystickInput(), 0);

		auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		auto& transformComponent2 = cube2.AddComponent<Fluky::TransformComponent>();
		transformComponent2.RotateXYZ(0.f, 0.f, 0.f);
		transformComponent2.SetTranslation(-1.5f, 0.f, 0.f);
		auto& playerComponent2 = cube2.AddComponent<Fluky::PlayerComponent>();
		playerComponent2.SetPlayerId(&world.GetJoystickInput(), 1);

	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			auto& player = gameObjects.at(i).GetComponent<Fluky::PlayerComponent>();
			auto& transf = gameObjects.at(i).GetComponent<Fluky::TransformComponent>();
			if (i == 0) {
				axeXP1 += player.GetAxes(1) * 0.1;
				axeYP1 += player.GetAxes(0) * 0.1;
				transf.RotateXY(1.f + axeXP1, 1.f + axeYP1);
			}
			else if (i == 1) {
				axeXP2 += player.GetAxes(1) * 0.1;
				axeYP2 += player.GetAxes(0) * 0.1;
				transf.RotateXY(1.f + axeXP2, 1.f + axeYP2);
			}
			
		}

		//world.GetJoystickInput();
		

	}

	float axeXP1 = 0;
	float axeYP1 = 0;

	float axeXP2 = 0;
	float axeYP2 = 0;

};

int main()
{
	EXWorld exworld;
	Fluky::Engine engine(exworld);
	engine.StartMainLoop();

}