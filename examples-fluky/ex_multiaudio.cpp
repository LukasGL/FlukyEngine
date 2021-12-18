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
		auto& audioComponent = cube.AddComponent<Fluky::AudioComponent>();
		audioComponent.SetPosition(0.f, 0.f, 0.f);

		auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		boxComponent2.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent2.SetPosition(1.5f, 0.f, 0.f);
		auto& playerComponent2 = cube2.AddComponent<Fluky::PlayerComponent>();
		playerComponent2.SetPlayerId(&world.GetJoystickInput(), 1);
		auto& audioComponent2 = cube2.AddComponent<Fluky::AudioComponent>();
		audioComponent2.SetPosition(0.f, 0.f, 0.f);
		audioComponent2.SetPitch(2.f);

		world.StartUpScene();

		audioComponent.Play("bounce.wav");
		audioComponent2.Play("bounce.wav");

	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			auto& audio = gameObjects.at(i).GetComponent<Fluky::AudioComponent>();
			auto& player = gameObjects.at(i).GetComponent<Fluky::PlayerComponent>();
			auto& box = gameObjects.at(i).GetComponent<Fluky::BoxComponent>();
			if (i == 0) {
				player.GetAxes(0);
				axeXP1 += player.GetAxes(0) * 0.1;
				axeYP1 -= (player.GetAxes(1) * 0.1);
				//axeZP1 -= player.GetAxes(3) * 0.1;
				box.SetPosition(axeXP1, axeYP1, axeZP1);
				audio.SetPosition( box.GetLocation(0), box.GetLocation(1), box.GetLocation(2));
			}
			else if (i == 1) {
				player.GetAxes(0);
				axeXP2 += player.GetAxes(0) * 0.1;
				axeYP2 -= (player.GetAxes(1) * 0.1);
				//axeZP2 -= player.GetAxes(3) * 0.1;
				box.SetPosition(axeXP2, axeYP2, axeZP2);
				audio.SetPosition( box.GetLocation(0), box.GetLocation(1), box.GetLocation(2));
			}


		}

		//world.GetJoystickInput();


	}

	float axeXP1 = 0;
	float axeYP1 = 0;
	float axeZP1 = 0;

	float axeXP2 = 0;
	float axeYP2 = 0;
	float axeZP2 = 0;

};

int main()
{
	EXWorld exworld;
	Fluky::Engine engine(exworld);
	engine.StartMainLoop();

}