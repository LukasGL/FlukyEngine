#pragma once
#ifndef INPUTCOMPONENT_HPP
#define INPUTCOMPONENT_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <cmath>
#include <ciso646>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>
/**
 * A simple struct handling all axes and button inputs of a joystick.
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

//std::ostream& operator<<(std::ostream& os, const Joystick& joystick)
//{
//    os << "buttons: ";
//    for (bool button : joystick.buttons)
//    {
//        os << (button ? 1 : 0);
//    }
//    os << " axes: ";
//    for (float ax : joystick.axes)
//    {
//        os << std::fixed << std::setprecision(2) << std::setfill('0') << ax << " ";
//    }
//    return os;
//}

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
    class InputComponent {

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
     * InputComponent
     *
     * Manages the joystick id after disconnections and connections
     *
     */
        void pollJoysticks();
        /**
     * InputComponent
     *
     * Sets the key callback for the current window
     *
     * @param  {GLFWwindow*} m_windowHandle :
     */
        static void SetKeyCallback(GLFWwindow* window);
        /**
     * InputComponent
     *
     * Sets the joystick callback
     *
     */
        static void SetJoystickCallback();
        /**
     * InputComponent
     *
     * Get the joysticks
     *
     * @return {JoystickContainer}  :
     */
        JoystickContainer& GetJoysticks();

        Joystick GetJoystick(float id);

        void SetPlayerId(float id) {
            PlayerId = id;
        }


        

    private:

        JoystickContainer joysticks;

        float PlayerId;

    };
}

#endif