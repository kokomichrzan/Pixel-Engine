#include "PixelEngine..h"

PixelEngine::PixelEngine(/* args */)
{
    //Create Window / UI
    Window = GraphicEngine::Create(WindowTitle);
    GUI UI = GUI(Window);

    //Get Assets
    Data::Vector Models = Data::Vector("Models");
    
    //While Loop
    while(!glfwWindowShouldClose(Window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.04f, 0.18f, 0.27f, 1.0f);



        UI.Render();
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }
}

PixelEngine::~PixelEngine()
{
    glfwDestroyWindow(Window);
    glfwTerminate();
}
