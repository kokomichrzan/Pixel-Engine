#pragma once
//GLAD / GLFW
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
//IMGUI
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
//Programs
#include "Scripts.h"
#include "../Macro.h"
#include "LOG.h"

//############################## Window ##############################//

namespace GraphicEngine
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

};

//############################## GUI ##############################//

class GUI
{
//############################## Elements ##############################//

private:
    struct Elements{
        private:
            int Type = 0;
            int ID = 0;
        public:
            Elements(int GetID);
            void Render();

    };

//Varibles
private:
    GLFWwindow* Window;
    int Width, Height;
    bool Dockspace = true;
    std::vector< Elements* > Windows;
    void Add();

public:
    bool WindowShouldClose = false;

//Functions
public:
    GUI(GLFWwindow* GetWindow);
    void Render();
    ~GUI();

};

