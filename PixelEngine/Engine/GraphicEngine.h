#pragma once
//LIBs
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
//Programs
#include "Data.h"
#include "LOG.h"

//############################## Window ##############################//

class GraphicEngine
{
private: //Programs
    LOG Log = LOG();
    
private: //Varibles
    double MouseLastX, MouseLastY, MouseX, MouseY;
    bool GetPoses = true, GetResize = true, ResizeLeftLock = false, ResizeRightLock = false, 
    ResizeTopLock = false, ResizeBottomLock = false, MoveLock = false;
    int WindowLastX, WindowLastY;
    int WindowWidth, WindowHeight;
    const int EventSize = 10;

private: // Window Behavior
    void Move(GLFWwindow* Window);
    void Resize(GLFWwindow* Window);

private: //Settings
    struct Settings{
        int Width = 1000,
        Height = 900,
        RefreshRate = 60;
        bool AutoResolution = false,
        FullScreen = false;
    };

public: //Functions
    GLFWwindow* CreateWindow(const std::string& WindowTitle = "");
    void Events(GLFWwindow* Window);
};