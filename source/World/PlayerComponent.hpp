#pragma once
#ifndef PLAYERCOMPONENT_HPP
#define PLAYERCOMPONENT_HPP

#include "../Platform/InputComponent.hpp"
#include <iostream>

namespace Fluky {
	/**
	 * Class in charge of the player controller and the joystick control assigned to a game object
	 * 
	 */ 
	class PlayerComponent {

	public:

		class Window;
  /**
	 * Sets the player id that will be the joystick that has control over a game object
   * 
   * @param  {InputComponent*} joyInput : 
   * @param  {float} id                 : 
   */
		void SetPlayerId(InputComponent *joyInput, float id) {
			PlayerId = id;
			p_joyInput = *joyInput;
			Update(*joyInput);
		}
  /**
	 * Returns a certain button boolean
   * 
   * @param  {int} ind : 
   * @return {bool}    : 
   */
		bool GetButtons(int ind) {
			if (!p_buttons.empty()) {
				return p_buttons[ind];
			}
			return false;
		}

  /**
	 * Returns a certain axe float value
   * 
   * @param  {int} ind : 
   * @return {float}   : 
   */
		float GetAxes(int ind) {
			if (!p_axes.empty()) {
				return p_axes[ind];
			}
			return 0;
		}

  /**
	 * player component updater
   * 
   * @param  {InputComponent} iP : 
   */
		void Update(InputComponent iP) {


			JoystickContainer& joysticks = iP.GetJoysticks();
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