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
        std::cout << "The event " << event  << std::endl;
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


    /* joysticks is not const as we detect connections and disconnections of joystics. */
    void JoystickInput::pollJoysticks()
    {
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



//void drawJoysticks(const JoystickContainer& joysticks, const gr::GPUShape& gpuButtonOff, const gr::GPUShape& gpuButtonOn, const gr::TransformShaderProgram& pipeline)
//{
//    for (auto& elem : joysticks)
//    {
//        auto& joystickId = elem.first;
//        auto& joystick = elem.second;
//
//        float const buttonSize = 2.0f / joystick.buttons.size();
//
//        float const verticalOffset = -1.0f + 3.0f * buttonSize * (joystickId + 1);
//
//        for (std::size_t buttonId = 0; buttonId < joystick.buttons.size(); ++buttonId)
//        {
//            gr::Matrix4f transform =
//                tr::translate(-1.0f + (0.5f * buttonSize) + buttonId * buttonSize, verticalOffset, 0) *
//                tr::uniformScale(buttonSize);
//            glUniformMatrix4fv(glGetUniformLocation(pipeline.shaderProgram, "transform"), 1, GL_FALSE, transform.data());
//
//            if (joystick.buttons[buttonId])
//            {
//                pipeline.drawCall(gpuButtonOn);
//            }
//            else
//            {
//                pipeline.drawCall(gpuButtonOff);
//            }
//
//        }
//
//        for (std::size_t axesId = 0; axesId < joystick.axes.size(); ++axesId)
//        {
//            gr::Matrix4f transformBackground =
//                tr::translate(-1.0f + (0.5f * buttonSize) + axesId * buttonSize, verticalOffset + buttonSize, 0) *
//                tr::uniformScale(buttonSize);
//            glUniformMatrix4fv(glGetUniformLocation(pipeline.shaderProgram, "transform"), 1, GL_FALSE, transformBackground.data());
//            pipeline.drawCall(gpuButtonOff);
//
//            gr::Matrix4f transform =
//                tr::translate(-1.0f + (0.5f * buttonSize) + axesId * buttonSize, verticalOffset + buttonSize + (joystick.axes[axesId] * buttonSize * 0.5f), 0) *
//                tr::uniformScale(buttonSize * 0.5);
//            glUniformMatrix4fv(glGetUniformLocation(pipeline.shaderProgram, "transform"), 1, GL_FALSE, transform.data());
//            pipeline.drawCall(gpuButtonOn);
//        }
//    }
//}


//int main()
//{
//    // Initialize glfw
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//    // Creating a glfw window
//    constexpr unsigned int SCR_WIDTH = 600;
//    constexpr unsigned int SCR_HEIGHT = 600;
//    std::string title = "ex_joystick";
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.c_str(), NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    // Connecting the callback function 'key_callback' to handle keyboard events
//    glfwSetKeyCallback(window, key_callback);
//
//    JoystickContainer joysticks;
//
//    glfwSetJoystickCallback(joystick_callback);
//
//    // Loading all OpenGL function pointers with glad
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // Creating our shader program and telling OpenGL to use it
//    
//    // Application loop
//    while (!glfwWindowShouldClose(window))
//    {
//        // Measuring performance
//        performanceMonitor.update(glfwGetTime());
//        std::stringstream ss;
//        ss << title << " " << performanceMonitor;
//        glfwSetWindowTitle(window, ss.str().c_str());
//
//        // Using GLFW to check and process input events
//        glfwPollEvents();
//
//        pollJoysticks(joysticks);
//
//        // Uncomment to print the joysticks' status to the standard output.
//        /*for (auto elem : joysticks)
//        {
//            auto& joystickId = elem.first;
//            auto& joystick = elem.second;
//            std::cout << joystickId << ") " << joystick << std::endl;
//        }*/
//
//        // Clearing the screen
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        drawJoysticks(joysticks, gpuButtonOff, gpuButtonOn, pipeline);
//
//        // Once the drawing is rendered, buffers are swap so an uncomplete drawing is never seen.
//        glfwSwapBuffers(window);
//    }
//
//    // freeing GPU memory
//    gpuButtonOn.clear();
//    gpuButtonOff.clear();
//
//    glfwTerminate();
//    return 0;
//}