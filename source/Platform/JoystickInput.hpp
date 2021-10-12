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
#include <GLFW/glfw3.h>
#include <memory>
/**
 * Struct that defines a Joystick
 * 
 */
struct Joystick
{
	std::vector<bool> buttons;
	std::vector<float> axes;

	Joystick(std::size_t const numberOfButtons, std::size_t const numberOfAxes) :
		buttons(numberOfButtons, false), axes(numberOfAxes, 0.0f)
	{
	}
};
/**
 * Stores the joystick ID
 * 
 */
using JoystickId = std::size_t;
/**
 * Joysticks container will store the created joysticks
 * 
 */
using JoystickContainer = std::unordered_map<JoystickId, Joystick>;

namespace Fluky
{
 /**
  * Defines the Joystick and Keyboard inputs
	* 
  */
	class JoystickInput {

	public:
		/**
     * 
     * Receives the keyboard events
     * 
     * @param  {GLFWwindow*} window : 
     * @param  {int} key            : 
     * @param  {int} scancode       : 
     * @param  {int} action         : 
     * @param  {int} mods           : 
     */
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		/**
     * 
     * Joystick callback, receives the joystick events
     * 
     * @param  {int} jid   : 
     * @param  {int} event : 
     */
		friend static void joystick_callback(int jid, int event);
		

		
		/**
     * JoystickInput 
     * 
     * Manages the joystick id after disconnections and connections
     * 
     */
		void pollJoysticks();
		/**
     * JoystickInput 
     * 
     * Sets the key callback for the current window
     * 
     * @param  {GLFWwindow*} m_windowHandle : 
     */
		static void SetKeyCallback(GLFWwindow* window);
		/**
     * JoystickInput 
     * 
     * Sets the joystick callback
     * 
     */
		static void SetJoystickCallback();
		/**
     * JoystickInput 
     * 
     * Get the joysticks 
     * 
     * @return {JoystickContainer}  : 
     */
		JoystickContainer GetJoysticks();

	private:

		JoystickContainer joysticks;
	};
}

#endif