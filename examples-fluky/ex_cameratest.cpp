#include "FlukyEngine.hpp"
#include <iostream>
#include <math.h>

class EXWorld : public Fluky::Application {
public:
	EXWorld() = default;
	~EXWorld() = default;
	virtual void UserStartUp(Fluky::World& world) noexcept override {

		auto cube = world.CreateGameObject();
		auto& boxComponent = cube.AddComponent<Fluky::BoxComponent>();
		auto& transformComponent = cube.AddComponent<Fluky::TransformComponent>();
		transformComponent.RotateXYZ(0.f, 0.f, 0.f);
		transformComponent.SetTranslation(0.0f, 0.f, 5.f);
		auto& playerComponent = cube.AddComponent<Fluky::PlayerComponent>();
		playerComponent.SetPlayerId(&world.GetJoystickInput(), 0);
		auto& cameraComponent = cube.AddComponent<Fluky::CameraComponent>();
		world.GetWindow().SetMainCamera(cameraComponent);
		cameraComponent.SetTranslation(0.f, 10.f, 15.f);

		auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		auto& transformComponent2 = cube2.AddComponent<Fluky::TransformComponent>();
		transformComponent2.RotateXYZ(0.f, 0.f, 0.f);
		transformComponent2.SetTranslation(-2.0f, 0.f, 0.f);

		auto cube3 = world.CreateGameObject();
		auto& boxComponent3 = cube3.AddComponent<Fluky::BoxComponent>();
		auto& transformComponent3 = cube3.AddComponent<Fluky::TransformComponent>();
		transformComponent3.RotateXYZ(0.f, 0.f, 0.f);
		transformComponent3.SetTranslation(0.0f, 0.f, 2.f);

		auto cube4 = world.CreateGameObject();
		auto& boxComponent4 = cube4.AddComponent<Fluky::BoxComponent>();
		auto& transformComponent4 = cube4.AddComponent<Fluky::TransformComponent>();
		transformComponent4.RotateXYZ(0.f, 0.f, 0.f);
		transformComponent4.SetTranslation(2.0f, 0.f, 0.f);

		world.StartUpScene();

	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			if (i == 0) {
				auto& player = gameObjects.at(i).GetComponent<Fluky::PlayerComponent>();
				auto& transf = gameObjects.at(i).GetComponent<Fluky::TransformComponent>();
				auto& camera = gameObjects.at(i).GetComponent<Fluky::CameraComponent>();
				player.GetAxes(0);
				axeLX += (player.GetAxes(0) > 0.1 || player.GetAxes(0) < -0.1) ? player.GetAxes(0) * 0.1 : 0;
				axeLY += (player.GetAxes(1) > 0.1 || player.GetAxes(1) < -0.1) ? player.GetAxes(1) * 0.1 : 0;
				axeRX += (player.GetAxes(2) > 0.1 || player.GetAxes(2) < -0.1) ? player.GetAxes(2) * 0.1 : 0;
				axeRY += (player.GetAxes(3) > 0.1 || player.GetAxes(3) < -0.1) ? player.GetAxes(3) * 0.1 : 0;


				//std::cout << player.GetAxes(0) << std::endl;
				//transf.SetTranslation(axeX, axeY, axeZ);
				//camera.SetAt(axeX, -axeY, axeZ);
				float radio = 10.f;
				float radio2 = 15.f;

				if (axeLY > 3.14) {
					axeLY -= player.GetAxes(1) * 0.1;
				}
				else if (axeLY < 0) {
					axeLY -= player.GetAxes(1) * 0.1;
				}

				//camera.SetTranslation(-axeLX, -axeLY, axeRY);
				float x = radio * sinf(-axeLX) * cosf(-axeLY);
				float y = radio * sinf(-axeLX) * sinf(-axeLY);
				float z = radio * cosf(-axeLX);
				transf.SetTranslation(x, y, z);
				//camera.SetTranslation(x, y , z);
				//std::cout << x << " " << y << " " << z << std::endl;
				std::cout << axeLY << std::endl;

				//camera.SetTranslation(-axeLX, -axeLY, 5.f);
				//camera.SetAt(-axeLX, axeLY, 0);
				//camera.SetEye(axeRX, axeRY, 5.0f);
				//camera.SetAt(radio * sin(-axeLX) * cos(-axeLY), radio * sin(-axeLX) * sin(-axeLY), radio * cos(-axeLX));
				//camera.SetEye(radio2*sin(-axeLX)*cos(-axeLY),0.f, radio2*cos(-axeLX));
				//camera.SetEye(radio * cos(axeX), radio * sin(axeX) * cos(axeY), -radio * sin(axeX) * sin(axeY));

			}



		}

		//world.GetJoystickInput();


	}

	float axeLX = 0;
	float axeLY = 0;
	float axeRX = 0;
	float axeRY = 10.f;

};

int main()
{
	EXWorld exworld;
	Fluky::Engine engine(exworld);
	engine.StartMainLoop();

}