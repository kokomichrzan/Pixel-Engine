#pragma once
//GLAD / GLFW
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>
//IMGUI
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
//Programs
#include "Scripts.h"
#include "../Macro.h"

//############################## Window ##############################//
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
//Varibles
private:
    float* RefreshRate;
//Functions
public:
    GUI(GLFWwindow* Window);
    void Render();
    ~GUI();
};

