#include "PixelEngine..h"

PixelEngine::PixelEngine(/* args */)
{
    Window = GraphicEngine::Create(WindowTitle);
    
    while(!glfwWindowShouldClose(Window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.04f, 0.18f, 0.27f, 1.0f);
        

        glfwPollEvents();
        glfwSwapBuffers(Window);
    }
}

PixelEngine::~PixelEngine()
{
}
