#include "FlukyEngine.hpp"


class EXInput : public Fluky::Application {
public:
	EXInput() = default;
	~EXInput() = default;
	virtual void UserStartUp(Fluky::World& world) noexcept override {

	}

	virtual void UserShutDown(Fluky::World& world) noexcept override {
	}
	virtual void UserUpdate(Fluky::World& world, float timeStep) noexcept override {

		auto& input = world.GetInput();
		if (input.IsMouseButtonPressed(FLUKY_MOUSE_BUTTON_1)) {
			auto mousePos = input.GetMousePosition();
			fprintf(stderr, "Mouse Button press At : (%f, %f).", mousePos.x, mousePos.y);
		}
	}
};

int main()
{
	EXInput exinput;
	Fluky::Engine engine(exinput);
	engine.StartMainLoop();

}