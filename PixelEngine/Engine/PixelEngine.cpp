#include "PixelEngine..h"

PixelEngine::PixelEngine(/* args */)
{
    Window = Window::Create(WindowTitle);
    
    while(!glfwWindowShouldClose(Window)){


        glfwPollEvents();
        glfwSwapBuffers(Window);
    }
}

PixelEngine::~PixelEngine()
{
}
