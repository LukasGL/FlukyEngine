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
		audioComponent.SetPosition(0.f,0.f,0.f);

		world.StartUpScene();

		audioComponent.Play("bounce.wav");

	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			auto& audio = gameObjects.at(i).GetComponent<Fluky::AudioComponent>();
			auto& player = gameObjects.at(i).GetComponent<Fluky::PlayerComponent>();
			auto& box = gameObjects.at(i).GetComponent<Fluky::BoxComponent>();
			player.GetAxes(0);
			axeX += player.GetAxes(0) * 0.1;
			axeY -= (player.GetAxes(1) * 0.1);
			axeZ -= player.GetAxes(3) * 0.1;
			box.SetPosition(axeX, axeY, axeZ);
			audio.SetPosition(box.GetLocation(0), box.GetLocation(1), box.GetLocation(2));


		}

		//world.GetJoystickInput();


	}

	float axeX = 0;
	float axeY = 0;
	float axeZ = 0;

};

int main()
{
	EXWorld exworld;
	Fluky::Engine engine(exworld);
	engine.StartMainLoop();

}