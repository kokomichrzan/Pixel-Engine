#include "PixelEngine..h"

PixelEngine::PixelEngine()
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
        //Set Background Color
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(.04f, 0.18f, 0.27f, 1.0f);

        //Render GUI
        UI.Render();

        //Check Window Size
        glfwGetWindowSize(Window, &Width, &Height);
        if(Width < 600) Width = 600;
        if(Height < 400) Height = 400;
        glfwSetWindowSize(Window, Width, Height); 

        //Log Change Res
        if(WidthBefore != Width || HeightBefore != Height) Log.INFO("Resolution Changed to " + std::to_string(Width) + " x " + std::to_string(Height));

        //Poll Event And Swap Buffer
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }
}

PixelEngine::~PixelEngine()
{
    //Save Window Size
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
