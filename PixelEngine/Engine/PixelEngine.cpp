#include "PixelEngine..h"

PixelEngine::PixelEngine()
    :Graphics(GraphicEngine()), Window(Graphics.CreateWindow()) //[OPTIMIZE]
{
    GUI UI = GUI(Window);
    
    while(!(glfwWindowShouldClose(Window) || UI.WindowShouldClose)){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(.04f, 0.18f, 0.27f, 1.0f);

        UI.Render();

        Graphics.Events(Window);

        glfwPollEvents();
        glfwSwapBuffers(Window);
    }

    Graphics.SaveWindowParams(Window);

    glfwDestroyWindow(Window);
    glfwTerminate();
}