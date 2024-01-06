#include "Application.h"

namespace PE {

    Application::Application()
        :Window(new PE::Window())
    {
        PE::GUI GUI = PE::GUI(Window);

        while (!GUI.WindowShouldClose) {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(.04f, 0.18f, 0.27f, 1.0f);

            Window->Events();

            GUI.Render();

            glfwPollEvents();
            glfwSwapBuffers(Window->HWindow);
        }


        delete Window;
    }
}