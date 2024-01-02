#pragma once
//PCH
#include <pch.h>
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
