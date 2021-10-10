#pragma once
#ifndef JOYSTICKINPUT_HPP
#define JOYSTICKINPUT_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <cmath>
#include <ciso646>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

struct Joystick
{
	std::vector<bool> buttons;
	std::vector<float> axes;

	Joystick(std::size_t const numberOfButtons, std::size_t const numberOfAxes) :
		buttons(numberOfButtons, false), axes(numberOfAxes, 0.0f)
	{
	}
};

using JoystickId = std::size_t;

using JoystickContainer = std::unordered_map<JoystickId, Joystick>;

namespace Fluky
{
	class JoystickInput {

	public:
		
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		friend static void joystick_callback(int jid, int event);
		

		

		void pollJoysticks();

		static void SetKeyCallback(GLFWwindow* window);

		static void SetJoystickCallback();

		JoystickContainer GetJoysticks();

	private:
		JoystickContainer joysticks;
	};
}

#endif