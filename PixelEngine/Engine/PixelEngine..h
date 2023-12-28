#pragma once
//LIBs
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
//Programs
#include "GraphicEngine.h"
#include "Gui.h"

class PixelEngine
{
private: //Programs
    GraphicEngine* Graphics;

private: //Varibles
    GLFWwindow* Window;

public: //Functions
    PixelEngine(/* args */);
    ~PixelEngine();

};
