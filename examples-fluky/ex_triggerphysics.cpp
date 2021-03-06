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
		boxComponent.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent.SetPosition(0.0f, 5.f, 5.f);
		boxComponent.SetShape(Fluky::Vec3(2.f, 1.f, 1.f));
		//boxComponent.SetShader("vs_cubes.bin", "fs_cubes.bin");
		boxComponent.SetShader("vs_bump.bin", "fs_bump.bin");
		boxComponent.SetTexture("fieldstone-rgba.dds", "fieldstone-n.dds");
		auto& playerComponent = cube.AddComponent<Fluky::PlayerComponent>();
		playerComponent.SetPlayerId(&world.GetJoystickInput(), 0);
		auto& cameraComponent = cube.AddComponent<Fluky::CameraComponent>();
		world.GetWindow().SetMainCamera(cameraComponent);
		cameraComponent.SetTranslation(0.f, 10.f, 15.f);
		auto& physicsCol = cube.AddComponent<Fluky::RigidBodyComponent>();
		physicsCol.CreateRigidBody(world, Fluky::Vec3(1.f, 1.f, 1.f), 10.f, Fluky::Vec3(0.f, 2.f, 0.f), 2, 1 | 3);
		boxComponent.AttachTo(physicsCol);

		auto callback = [physicsCol](Fluky::World& world, Fluky::RigidBodyComponent& otherRigidBody, bool isSwaped, Fluky::CollisionInformation& colInfo) mutable {
			std::cout << "cubo colisiona" << std::endl;
		};
		physicsCol.SetStartCollisionCallback(callback);

		auto cube2 = world.CreateGameObject();
		auto& boxComponent2 = cube2.AddComponent<Fluky::BoxComponent>();
		boxComponent2.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent2.SetPosition(10.0f, 0.f, 0.f);
		boxComponent2.SetShape(Fluky::Vec3(100.f, 0.5f, 100.f));
		/*boxComponent2.SetShader("vs_cubes.bin", "fs_cubes.bin");*/
		boxComponent2.SetShader("vs_bump.bin", "fs_bump.bin");
		boxComponent2.SetTexture("fieldstone-rgba.dds", "fieldstone-n.dds");
		auto& physicsCol2 = cube2.AddComponent<Fluky::RigidBodyComponent>();
		physicsCol2.CreateRigidBody(world, Fluky::Vec3(100.f, 1.f, 100.f), 0.f, Fluky::Vec3(0.f, 0.f, 0.f), 1, 2 | 3 | 4);
		auto& triggerBody = cube2.AddComponent<Fluky::CollisionTriggerComponent>();

		auto cube3 = world.CreateGameObject();
		auto& boxComponent3 = cube3.AddComponent<Fluky::BoxComponent>();
		boxComponent3.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent3.SetPosition(0.0f, 0.f, 2.f);
		boxComponent3.SetShape(Fluky::Vec3(0.5f, 1.f, 2.f));
		//boxComponent3.SetShader("vs_cubes.bin", "fs_cubes.bin");
		boxComponent3.SetShader("vs_bump.bin", "fs_bump.bin");
		boxComponent3.SetTexture("fieldstone-rgba.dds", "fieldstone-n.dds");
		auto& playerComponent2 = cube2.AddComponent<Fluky::PlayerComponent>();
		playerComponent2.SetPlayerId(&world.GetJoystickInput(), 1);
		auto& physicsCol3 = cube3.AddComponent<Fluky::RigidBodyComponent>();
		physicsCol3.CreateRigidBody(world, Fluky::Vec3(1.f, 1.f, 1.f), 10.f, Fluky::Vec3(0.f, 30.f, 1.f), 3, 1 | 2);
		boxComponent3.AttachTo(physicsCol3);

		auto cube4 = world.CreateGameObject();
		auto& boxComponent4 = cube4.AddComponent<Fluky::BoxComponent>();
		boxComponent4.RotateXYZ(0.f, 0.f, 0.f);
		boxComponent4.SetPosition(2.0f, 0.f, 0.f);
		//boxComponent4.SetShader("vs_cubes.bin", "fs_cubes.bin");
		boxComponent4.SetShader("vs_bump.bin", "fs_bump.bin");
		boxComponent4.SetTexture("fieldstone-rgba.dds", "fieldstone-n.dds");
		auto& physicsCol4 = cube4.AddComponent<Fluky::RigidBodyComponent>();
		physicsCol4.CreateRigidBody(world, Fluky::Vec3(1.f, 1.f, 1.f), 10.f, Fluky::Vec3(1.f, 30.f, 0.f), 4, 1);
		boxComponent4.AttachTo(physicsCol4);

		world.StartUpScene();


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
				player.GetAxes(0);
				axeLX = (player.GetAxes(0) > 0.1 || player.GetAxes(0) < -0.1) ? player.GetAxes(0) * 15 : 0;
				axeLY = (player.GetAxes(1) > 0.1 || player.GetAxes(1) < -0.1) ? player.GetAxes(1) * 15 : 0;
				axeRX += (player.GetAxes(2) > 0.1 || player.GetAxes(2) < -0.1) ? player.GetAxes(2) * 0.01 : 0;
				axeRY += (player.GetAxes(3) > 0.1 || player.GetAxes(3) < -0.1) ? player.GetAxes(3) * 0.01 : 0;


				//std::cout << player.GetAxes(0) << std::endl;
				//transf.SetTranslation(axeX, axeY, axeZ);
				//camera.SetAt(axeX, -axeY, axeZ);
				float radio = 10.f;
				float radio2 = 15.f;


				//camera.SetTranslation(-axeLX, -axeLY, axeRY);
				float x = radio * sinf(-axeLX) * cosf(-axeLY);
				float y = radio * sinf(-axeLX) * sinf(-axeLY);
				float z = radio * cosf(-axeLX);
				//box.SetPosition(colobj.GetLocation().x, colobj.GetLocation().y, colobj.GetLocation().z);

				//colobj.SetPosition(Fluky::Vec3(colobj.GetLocation().x - axeLX, colobj.GetLocation().y, colobj.GetLocation().z + axeLY));
				colobj.SetPosition(Fluky::Vec3(-axeLX, 0.f, axeLY));

				//std::cout << rigidBody->getLinearVelocity().getX() << " " << rigidBody->getLinearVelocity().getY() << " " << rigidBody->getLinearVelocity().getZ() << std::endl;
				//world.GetPhysicsSystem().SetPositionRigidBody(colobj, Fluky::Vec3(-axeLX, 0.f, 0.f));


				//std::cout << colobj.GetLocation().x << " " << colobj.GetLocation().y<< " " << colobj.GetLocation().z << std::endl;
				//std::cout << box.GetLocation(0) << " " << box.GetLocation(1) << " " << box.GetLocation(2) << std::endl;

			}
			else if (i == 1) {
				//auto& colobj = gameObjects.at(i).GetComponent<Fluky::RigidBodyComponent>();
				//colobj.SetPosition(Fluky::Vec3(sin(time), 2.f, 0.f));
				auto& player = gameObjects.at(i).GetComponent<Fluky::PlayerComponent>();

				axeLX_P2 += (player.GetAxes(0) > 0.1 || player.GetAxes(0) < -0.1) ? player.GetAxes(0) * 15 : 0;
				axeLY_P2 += (player.GetAxes(1) > 0.1 || player.GetAxes(1) < -0.1) ? player.GetAxes(1) * 15 : 0;
				axeRX_P2 += (player.GetAxes(2) > 0.1 || player.GetAxes(2) < -0.1) ? player.GetAxes(2) * 0.01 : 0;
				axeRY_P2 += (player.GetAxes(3) > 0.1 || player.GetAxes(3) < -0.1) ? player.GetAxes(3) * 0.01 : 0;

				float radio = 50.f;

				float x = radio * sinf(-axeRY_P2) * cosf(axeRX_P2);
				float y = radio * cosf(-axeRY_P2);
				float z = radio * sinf(-axeRY_P2) * sinf(axeRX_P2);

				world.GetWindow().SetLightRadius(radio);

				world.GetWindow().SetLightPos(Fluky::Vec3(x, y, z));

				
			}



		}

		//world.GetJoystickInput();


	}

	float axeLX = 0;
	float axeLY = 0;
	float axeRX = 0;
	float axeRY = 10.f;

	float axeLX_P2 = 0;
	float axeLY_P2 = 0;
	float axeRX_P2 = 0;
	float axeRY_P2 = 10.f;

};

int main()
{
	EXWorld exworld;
	Fluky::Engine engine(exworld);
	engine.StartMainLoop();

}