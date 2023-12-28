#include "PixelEngine..h"

PixelEngine::PixelEngine()
{
    //Create Window / UI
    GraphicEngine Graphics = GraphicEngine();
    Window = Graphics.CreateWindow(WindowTitle);
    GUI UI = GUI(Window);
    
    //While Loop
    while(!(glfwWindowShouldClose(Window) || UI.WindowShouldClose)){
        //Set Background Color
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(.04f, 0.18f, 0.27f, 1.0f);

        //Render GUI
        UI.Render();

        //Events Window
        Graphics.Events(Window);

        //Poll Event And Swap Buffer
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }
}

PixelEngine::~PixelEngine()
{
    //Save Window Size
    glfwGetWindowSize(Window, &Width, &Height);
    Data::Array WindowSettings = Data::Array("Settings", 5);
    WindowSettings.Read("Window");
    WindowSettings.Content[2] = std::to_string(Width);
    WindowSettings.Content[3] = std::to_string(Height);
    WindowSettings.Save("Window");
    Log.MESSAGE("Window Size Saved");

    //Destroy Window
    glfwDestroyWindow(Window);
    glfwTerminate();
}
