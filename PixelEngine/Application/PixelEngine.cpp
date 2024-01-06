#include "PixelEngine..h"

//void* operator new(size_t size) {
//
//    return malloc(size);
//}

PixelEngine::PixelEngine()
    :Graphics(GraphicEngine(Window)), 
    UI(GUI(Window))
{
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

    //Destroy Window
    glfwDestroyWindow(Window);
    glfwTerminate();
    Graphics.SaveWindowParams(Window);
}


int main() {
    PixelEngine App = PixelEngine();
    return 0;
}