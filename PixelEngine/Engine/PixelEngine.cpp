#include "PixelEngine..h"

PixelEngine::PixelEngine(/* args */)
{
    //Create Window / UI
    Window = GraphicEngine::Create(WindowTitle);
    GUI UI = GUI(Window);

    //Get Assets
    Data::Vector Models = Data::Vector("Models"); Log.MESSAGE("Opened Models Dir");
    Data::Vector Textures = Data::Vector("Textures"); Log.MESSAGE("Opened Textures Dir");
    Data::Vector Materials = Data::Vector("Materials"); Log.MESSAGE("Opened Materials Dir");
    
    //While Loop
    while(!(glfwWindowShouldClose(Window) || UI.WindowShouldClose)){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(.04f, 0.18f, 0.27f, 1.0f);

        UI.Render();

        int Width, Height;
        glfwGetWindowSize(Window, &Width, &Height);
        if(Width < 600) Width = 600;
        if(Height < 400) Height = 400;
        glfwSetWindowSize(Window, Width, Height); 
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }
}

PixelEngine::~PixelEngine()
{
    int Width, Height;
    glfwGetWindowSize(Window, &Width, &Height);
    Data::Array WindowSettings = Data::Array("Data", 5);
    WindowSettings.Read("Settings");
    WindowSettings.Content[2] = std::to_string(Width);
    WindowSettings.Content[3] = std::to_string(Height);
    WindowSettings.Save("Settings");
    Log.MESSAGE("Window Size Saved");
    glfwDestroyWindow(Window);
    glfwTerminate();
}
