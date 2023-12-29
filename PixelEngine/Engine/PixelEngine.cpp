#include "PixelEngine..h"

PixelEngine::PixelEngine()
    :Graphics(new GraphicEngine()), Window(Graphics->CreateWindow())
{
    //Create UI
    GUI UI = GUI(Window);
    
    //While Loop
    while(!(glfwWindowShouldClose(Window) || UI.WindowShouldClose)){
        //Set Background Color
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(.04f, 0.18f, 0.27f, 1.0f);

        //Render GUI
        UI.Render();

        //Events Window
        Graphics->Events(Window);

        //Poll Event And Swap Buffer
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }

}

PixelEngine::~PixelEngine()
{
    //Save Window Params
    Graphics->SaveWindowParams(Window);

    //Remove Graphics
    delete Graphics;

    //Destroy Window
    glfwDestroyWindow(Window);
    glfwTerminate();

}
