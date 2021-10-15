#include "JoystickInput.hpp"

void joystick_callback(int jid, int event);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);



namespace Fluky {

    
    
    
    void joystick_callback(int jid, int event)
    {
        if (event == GLFW_CONNECTED)
        {
            // The joystick was connected
            std::cout << "The joystick " << jid << " was connected" << std::endl;
        }
        else if (event == GLFW_DISCONNECTED)
        {
            // The joystick was disconnected
            std::cout << "The joystick " << jid << " was disconnected" << std::endl;
        }
    }
    
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }
    
    void JoystickInput::SetKeyCallback(GLFWwindow* m_windowHandle)
    {
        glfwSetKeyCallback(m_windowHandle, key_callback);
    }
    
    void JoystickInput::SetJoystickCallback()
    {
        glfwSetJoystickCallback(joystick_callback);
    }
    
    JoystickContainer JoystickInput::GetJoysticks()
    {
        return this->joysticks;
    }


    
    
    void JoystickInput::pollJoysticks()
    {
        for (auto& elem : joysticks)
        {
            auto& joystickId = elem.first;
            auto& joystick = elem.second;

            float const buttonSize = 2.0f / joystick.buttons.size();
        }

        for (int joystickId = GLFW_JOYSTICK_1; joystickId < GLFW_JOYSTICK_LAST; ++joystickId)
        {
            int const joystickConnected = glfwJoystickPresent(joystickId);
            if (joystickConnected == GLFW_FALSE)
            {
                if (joysticks.count(joystickId) != 0)
                {
                    /* joystickId has been disconnected.*/
                    joysticks.erase(joystickId);
                }
                continue;
            }

            // At this point we have a joystick with this id.
            if (joysticks.count(joystickId) == 0)
            {
                /* joystickId has been connected.*/

                int buttonsCount;
                glfwGetJoystickButtons(joystickId, &buttonsCount);

                int axesCount;
                glfwGetJoystickAxes(joystickId, &axesCount);

                joysticks.emplace(joystickId, Joystick(buttonsCount, axesCount));
            }

            Joystick& joystick = joysticks.at(joystickId);

            int buttonsCount;
            const unsigned char* buttons = glfwGetJoystickButtons(joystickId, &buttonsCount);

            for (int buttonId = 0; buttonId < buttonsCount; ++buttonId)
            {
                joystick.buttons[buttonId] = buttons[buttonId] == GLFW_PRESS;
            }

            int axesCount;
            const float* axes = glfwGetJoystickAxes(joystickId, &axesCount);

            for (int axesId = 0; axesId < axesCount; ++axesId)
            {
                joystick.axes[axesId] = axes[axesId];
            }
        }
    }

}