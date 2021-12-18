#include "FlukyEngine.hpp"
#include <iostream>

class EXWorld : public Fluky::Application {
public:
	EXWorld() = default;
	~EXWorld() = default;
	virtual void UserStartUp(Fluky::World& world) noexcept override {

		auto cube = world.CreateGameObject();
		auto& boxComponent = cube.AddComponent<Fluky::BoxComponent>();
		boxComponent.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent.SetPosition(1.5f, 0.f, 0.f);
		auto& playerComponent = cube.AddComponent<Fluky::PlayerComponent>();
		playerComponent.SetPlayerId(&world.GetJoystickInput(), 0);

		auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		boxComponent2.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent2.SetPosition(-1.5f, 0.f, 0.f);
		auto& playerComponent2 = cube2.AddComponent<Fluky::PlayerComponent>();
		playerComponent2.SetPlayerId(&world.GetJoystickInput(), 1);

		world.StartUpScene();
	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			auto& player = gameObjects.at(i).GetComponent<Fluky::PlayerComponent>();
			auto& box = gameObjects.at(i).GetComponent<Fluky::BoxComponent>();
			if (i == 0) {
				axeXP1 += player.GetAxes(1) * 0.1;
				axeYP1 += player.GetAxes(0) * 0.1;
				box.RotateXY(0.f + axeXP1, 0.f + axeYP1);
				std::cout << "---------------------------" << std::endl;
				for (int i = 0; i < 16; i++) {
					std::cout << box.GetMatrix()[i] << std::endl;
				}
				std::cout << "---------------------------" << std::endl;

			}
			else if (i == 1) {
				axeXP2 += player.GetAxes(1) * 0.1;
				axeYP2 += player.GetAxes(0) * 0.1;
				box.RotateXY(1.f + axeXP2, 1.f + axeYP2);
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