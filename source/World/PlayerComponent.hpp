#pragma once
#ifndef PLAYERCOMPONENT_HPP
#define PLAYERCOMPONENT_HPP

#include "../Platform/InputComponent.hpp"
#include <iostream>

namespace Fluky {

	class PlayerComponent {

	public:

		class Window;

		void SetPlayerId(InputComponent *joyInput, float id) {
			PlayerId = id;
			p_joyInput = *joyInput;
			Update();
		}

		std::vector<bool>& GetButtons() {
			return p_buttons;
		}

		std::vector<float>& GetAxes() {
			return p_axes;
		}

		void Update() {


			JoystickContainer& joysticks = p_joyInput.GetJoysticks();
			for (auto& elem : joysticks)
			{
				auto& joystickId = elem.first;
				auto joystick = elem.second;

				if (joystickId == PlayerId)
				{
					p_axes = joystick.axes;

					p_buttons = joystick.buttons;
				}
			}


		}


		

	private:

		float PlayerId;

		std::vector<float> p_axes;

		std::vector<bool> p_buttons;

		InputComponent p_joyInput;


	};

}

#endif