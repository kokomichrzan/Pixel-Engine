#pragma once
//LIBs
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
#include "LOG.h"

//############################## Window ##############################//

namespace GraphicEngine
{
    GLFWwindow* Create(const std::string& WindowTitle);
    
    //Settings
    struct Settings{
        int Width = 1000,
        Height = 900,
        RefreshRate = 60;
        bool AutoResolution = false,
        FullScreen = false;
    };

};

//############################## Element ##############################//

class Element{
    public:
        int Type = 0;
        int ID = 0;
    public:
        Element(const int& GetID, int GetType = 0);
        void Render();

};

//############################## GUI ##############################//

class GUI
{
//Varibles
private:
    GLFWwindow* Window;
    int Width, Height;
    bool Dockspace = true;
    std::vector<Element*> SubWindow;

    //############################## GUI Events ##############################//
    
    void CreateNewSubWindow();

public:
    bool WindowShouldClose = false;

//Functions
public:
    GUI(GLFWwindow* GetWindow);
    void Render();
    ~GUI();

};