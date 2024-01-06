#pragma once
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "GraphicEngine.h"
#include "Gui.h"

class PixelEngine
{
private:
    GraphicEngine Graphics;
    GLFWwindow* Window;

public:
    PixelEngine();

};
