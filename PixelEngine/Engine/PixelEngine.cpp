#include "PixelEngine..h"

PixelEngine::PixelEngine(/* args */)
{
    //Create Window / UI
    Window = GraphicEngine::Create(WindowTitle);
    GUI UI = GUI(Window);

    //Get Assets
    Data::Vector Models = Data::Vector("Models");
    Data::Vector Textures = Data::Vector("Textures");
    Data::Vector Materials = Data::Vector("Materials");
    
    //While Loop
    while(!glfwWindowShouldClose(Window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.04f, 0.18f, 0.27f, 1.0f);

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
    glfwDestroyWindow(Window);
    glfwTerminate();
}
