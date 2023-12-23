#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include "GraphicEngine.h"
#include "Scripts.h"

class PixelEngine
{
private:
    const std::filesystem::path ExecutePath = std::filesystem::current_path();
    const std::string WindowTitle = "Pixel Engine";
    GLFWwindow* Window;


public:
    PixelEngine(/* args */);
    ~PixelEngine();
};
