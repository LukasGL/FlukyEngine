#include "FlukyEngine.hpp"
#include <iostream>
#include <math.h>
#include <random>

class FloorAndWalls : public Fluky::Application {
public:
	FloorAndWalls() = default;
	~FloorAndWalls() = default;

	virtual void UserStartUp(Fluky::World& world) noexcept override {


		std::vector<const char*> textures = { "Plastic008_1K_Color.dds", "Plastic008_1K_Color_1.dds", "Plastic008_1K_Color_2.dds", "Plastic008_1K_Color_1.dds", "Plastic008_1K_Color_3.dds"
		, "Plastic008_1K_Color_4.dds" , "Plastic008_1K_Color_5.dds", "Plastic008_1K_Color_6.dds" };

		int xinit = 3;
		int yinit = 3;

		Fluky::Vec3 floorSize = Fluky::Vec3(25.f, 1.f, 25.f);

		auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		boxComponent2.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent2.SetShape(floorSize);
		boxComponent2.SetShader("vs_bump.bin", "fs_bump.bin");
		boxComponent2.SetTexture("Bricks074_1K_Color.dds", "Bricks074_1K_NormalDX.dds");
		boxComponent2.SetPosition(0.f, -1.f, 0.f);
		auto& physicsCol2 = cube2.AddComponent<Fluky::RigidBodyComponent>();
		physicsCol2.CreateRigidBody(world, floorSize, 0.f, Fluky::Vec3(0.f, -1.f, 0.f), 1, 2 | 3 | 4);

	}
	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {}

};

class BigCubeofCubes : public Fluky::Application {
public:
	BigCubeofCubes() = default;
	~BigCubeofCubes() = default;

	virtual void UserStartUp(Fluky::World& world) noexcept override {
		
		int bigCubeSize = 6;

		std::vector<const char*> textures = { "Plastic008_1K_Color.dds", "Plastic008_1K_Color_1.dds", "Plastic008_1K_Color_2.dds", "Plastic008_1K_Color_1.dds", "Plastic008_1K_Color_3.dds"
		, "Plastic008_1K_Color_4.dds" , "Plastic008_1K_Color_5.dds" };

		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, 6); // define the range

		std::uniform_int_distribution<> distrCube(0, bigCubeSize-1); // define the range

		int randomCube[3] = { distrCube(gen), distrCube(gen) , distrCube(gen) };

		int xinit = 3;
		int yinit = 3;
		int zinit = 3;

		float cubesSize = 0.5f;

		for (int i = 0; i < bigCubeSize; i++) {
			for (int j = 0; j < bigCubeSize; j++) {
				for (int k = 0; k < bigCubeSize; k++) {
					if (randomCube[0] == i && randomCube[1] == j && randomCube[2] == k) {
						auto cube2 = world.CreateGameObject();
						auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
						boxComponent2.RotateXYZ(0.f, 0.f, 0.f);
						boxComponent2.SetShape(Fluky::Vec3(cubesSize, cubesSize, cubesSize));
						boxComponent2.SetShader("vs_bump.bin", "fs_bump.bin");
						boxComponent2.SetTexture("Plastic008_1K_Color_6.dds", "Plastic008_1K_NormalGL.dds");
						auto& physicsCol2 = cube2.AddComponent<Fluky::RigidBodyComponent>();
						physicsCol2.CreateRigidBody(world, Fluky::Vec3(cubesSize, cubesSize, cubesSize), 10.f, Fluky::Vec3(-xinit + i * cubesSize, yinit - j * cubesSize, zinit - k * cubesSize), 2, 1 | 2 | 3 | 4);
						auto& triggerBody = cube2.AddComponent<Fluky::CollisionTriggerComponent>();
						boxComponent2.AttachTo(physicsCol2);
						auto callback = [physicsCol2](Fluky::World& world, Fluky::RigidBodyComponent& otherRigidBody, bool isSwaped, Fluky::CollisionInformation& colInfo) mutable {
							auto& prinPlayerRigidBody = world.GetGameObjects().at(0).GetComponent<Fluky::RigidBodyComponent>();
							if (prinPlayerRigidBody.equal(otherRigidBody)) {
								std::cout << "Ganaste!" << std::endl;
							}

						};
						physicsCol2.SetStartCollisionCallback(callback);
					}
					else {
						auto cube2 = world.CreateGameObject();
						auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
						boxComponent2.RotateXYZ(0.f, 0.f, 0.f);
						boxComponent2.SetShape(Fluky::Vec3(cubesSize, cubesSize, cubesSize));
						boxComponent2.SetShader("vs_bump.bin", "fs_bump.bin");
						boxComponent2.SetTexture(textures.at(distr(gen)), "Plastic008_1K_NormalGL.dds");
						auto& physicsCol2 = cube2.AddComponent<Fluky::RigidBodyComponent>();
						physicsCol2.CreateRigidBody(world, Fluky::Vec3(cubesSize, cubesSize, cubesSize), 10.f, Fluky::Vec3(-xinit + i * cubesSize, yinit - j * cubesSize, zinit - k * cubesSize), 2, 1 | 2 | 3 | 4);
						boxComponent2.AttachTo(physicsCol2);
					}
				}
			}
		}

		/*auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		boxComponent2.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent2.SetShape(Fluky::Vec3(0.5f, 0.5f, 0.5f));
		boxComponent2.SetShader("vs_bump.bin", "fs_bump.bin");
		boxComponent2.SetTexture(textures.at(0), "Plastic008_1K_NormalGL.dds");
		boxComponent2.SetPosition(2.f,3.f, 10.f);
		auto& physicsCol2 = cube2.AddComponent<Fluky::RigidBodyComponent>();
		physicsCol2.CreateRigidBody(world, Fluky::Vec3(0.5f, 0.5f, 0.5f), 10.f, Fluky::Vec3(2.f, 3.f, 10.f), 2, 1 | 2 | 3 | 4);
		auto& triggerBody = cube2.AddComponent<Fluky::CollisionTriggerComponent>();
		boxComponent2.AttachTo(physicsCol2);*/
	
	}
	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {}

};

class EXWorld : public Fluky::Application {
public:
	EXWorld() = default;
	~EXWorld() = default;
	virtual void UserStartUp(Fluky::World& world) noexcept override {

		auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		boxComponent2.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent2.SetShape(Fluky::Vec3(0.5f, 0.5f, 0.5f));
		boxComponent2.SetShader("vs_bump.bin", "fs_bump.bin");
		boxComponent2.SetTexture("Bricks074_1K_Color.dds", "Bricks074_1K_NormalDX.dds");
		auto& physicsCol2 = cube2.AddComponent<Fluky::RigidBodyComponent>();
		physicsCol2.CreateRigidBody(world, Fluky::Vec3(0.5f, 0.5f, 0.5f), 10.f, Fluky::Vec3(2.0f, 0.f, 0.f), 2, 1 | 2 | 3 | 4);
		boxComponent2.AttachTo(physicsCol2);
		auto& cameraComponent = cube2.AddComponent<Fluky::CameraComponent>();
		world.GetWindow().SetMainCamera(cameraComponent);
		cameraComponent.SetTranslation(0.f, -10.f, 0.f);
		auto& playerComponent2 = cube2.AddComponent<Fluky::PlayerComponent>();
		playerComponent2.SetPlayerId(&world.GetJoystickInput(), 0);
		auto& audioComponent = cube2.AddComponent<Fluky::AudioComponent>();
		audioComponent.SetPosition(0.f, 0.f, 0.f);

		/*
		auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		boxComponent2.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent2.SetPosition(-2.0f, 0.f, 0.f);
		boxComponent2.SetShader("vs_bump.bin", "fs_bump.bin");
		boxComponent2.SetTexture("Plastic008_1K_Color_1.dds", "Plastic008_1K_NormalGL.dds");

		auto cube3 = world.CreateGameObject();
		auto& boxComponent3 = cube3.AddComponent<Fluky::BoxComponent>();
		boxComponent3.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent3.SetPosition(0.0f, 0.f, 2.f);
		boxComponent3.SetShader("vs_bump.bin", "fs_bump.bin");
		boxComponent3.SetTexture("Plastic008_1K_Color_2.dds", "Plastic008_1K_NormalGL.dds");*/

		BigCubeofCubes bigCube;
		bigCube.UserStartUp(world);

		FloorAndWalls floornWalls;
		floornWalls.UserStartUp(world);


		world.StartUpScene();

		audioComponent.Play("bounce.wav");


	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep, float time) noexcept override {
		auto gameObjects = world.GetGameObjects();

		for (int i = 0; i < gameObjects.size(); i++) {
			if (i == 0) {
				auto& player = gameObjects.at(i).GetComponent<Fluky::PlayerComponent>();
				auto& box = gameObjects.at(i).GetComponent<Fluky::BoxComponent>();
				auto& camera = gameObjects.at(i).GetComponent<Fluky::CameraComponent>();
				auto& colobj = gameObjects.at(i).GetComponent<Fluky::RigidBodyComponent>();
				auto& audio = gameObjects.at(i).GetComponent<Fluky::AudioComponent>();
				player.GetAxes(0);
				axeLX = (player.GetAxes(0) > 0.1 || player.GetAxes(0) < -0.1) ? player.GetAxes(0) * 2 : 0;
				axeLY = (player.GetAxes(1) > 0.1 || player.GetAxes(1) < -0.1) ? player.GetAxes(1) * 2 : 0;
				axeRX += (player.GetAxes(2) > 0.1 || player.GetAxes(2) < -0.1) ? player.GetAxes(2) * 0.01 : 0;
				axeRY += (player.GetAxes(3) > 0.1 || player.GetAxes(3) < -0.1) ? player.GetAxes(3) * 0.01 : 0;


				float radio = 20.f;
				float radio2 = 15.f;

				axeRX = fmodf(axeRX, 2 * 3.14f);
				axeRY = fmodf(axeRY, 3.14f);

				float x = radio * sinf(-axeRY) * cosf(axeRX);
				float y = radio * cosf(-axeRY);
				float z = radio * sinf(-axeRY) * sinf(axeRX);
				camera.SetTranslation(x, y, z);
				camera.SetEye(-axeLX, 0.f, axeLY);

				colobj.SetPosition(Fluky::Vec3(-axeLX, 0.f, axeLY));

				audio.SetPosition(-axeLX, 0.f, axeLY);

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