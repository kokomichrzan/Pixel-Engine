#pragma once
//LIBs
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
//Programs
#include "GraphicEngine.h"
#include "Gui.h"
#include "Data.h"
#include "LOG.h"

class PixelEngine
{
private: //Programs
    LOG Log = LOG();

private: //Varibles
    int Width, Height;
    const std::filesystem::path ExecutePath = std::filesystem::current_path();
    const std::string WindowTitle = "Pixel Engine";
    GLFWwindow* Window;

public: //Functions
    PixelEngine(/* args */);
    ~PixelEngine();

};
