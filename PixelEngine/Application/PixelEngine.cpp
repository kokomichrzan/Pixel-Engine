#include "PixelEngine..h"

PixelEngine::PixelEngine()
    :Graphics(GraphicEngine()), Window(Graphics.CreateWindow()) //[OPTIMIZE]
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
        Graphics.Events(Window);

        //Poll Event And Swap Buffer
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }

    //Save Window Params
    Graphics.SaveWindowParams(Window);

    //Destroy Window
    glfwDestroyWindow(Window);
    glfwTerminate();
}

#ifdef _DEBUG
int main() {
    PixelEngine App = PixelEngine();
    return 0;
}
#else
int WinMain() {
    PixelEngine App = PixelEngine();
    return 0;
}
#endif