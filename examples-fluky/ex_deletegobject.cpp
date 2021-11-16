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

		world.StartUpScene();


	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			auto& player = gameObjects.at(i).GetComponent<Fluky::PlayerComponent>();
			auto& transf = gameObjects.at(i).GetComponent<Fluky::TransformComponent>();
			player.GetAxes(0);
			axeX += player.GetAxes(0) * 0.1;
			axeY -= (player.GetAxes(1) * 0.1);
			axeZ -= player.GetAxes(3) * 0.1;
			transf.SetTranslation(axeX, axeY, axeZ);

			if (player.GetButtons(0) && !bTriggered) {
				std::cout << "GameObject eliminado" << std::endl;
				bTriggered = true;
				world.ShutDownGameObject(gameObjects.at(i));
			}
		}
		std::cout << "GameObjects: " << gameObjects.size() << std::endl;
		

		//world.GetJoystickInput();


	}

	bool bTriggered = false;

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