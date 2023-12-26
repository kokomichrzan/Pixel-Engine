#pragma once
//LIBs
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
//Programs
#include "GraphicEngine.h"
#include "Scripts.h"
#include "LOG.h"

class PixelEngine
{
private:
    LOG Log = LOG();
    int Width, Height;
    const std::filesystem::path ExecutePath = std::filesystem::current_path();
    const std::string WindowTitle = "Pixel Engine";
    GLFWwindow* Window;


public:
    PixelEngine(/* args */);
    ~PixelEngine();
};
