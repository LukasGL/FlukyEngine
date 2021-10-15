#include "FlukyEngine.hpp"


class EXWorld : public Fluky::Application {
public:
	EXWorld() = default;
	~EXWorld() = default;
	virtual void UserStartUp(Fluky::World& world) noexcept override {
		//world.PlayWav("demo.wav");
	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {

	}
	virtual void UserUpdate(Fluky::World& world, float timeStep) noexcept override {
	}
};

int main()
{
	EXWorld exworld;
	Fluky::Engine engine(exworld);
	engine.StartMainLoop();

}