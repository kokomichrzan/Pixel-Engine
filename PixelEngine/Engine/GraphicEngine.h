#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Scripts.h"

//############################## Window ##############################//
namespace Window
{
    GLFWwindow* Create(const std::string WindowTitle);

    //Settings
    struct Settings{
        int Width = 1000,
        Height = 900,
        RefreshRate = 60;
        bool AutoResolution = false,
        FullScreen = false;
    };

}