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
#include "LOG.h"
#include "Data.h"

//############################## Element ##############################//

class Element{
private: //Programs
    LOG Log = LOG();

public: //Element Varibles
    int Type = 0;
    int ID = 0;
    bool RenderElement = true;

private: //Element Type Data
    //Get Assets
    Data::Vector Models = Data::Vector("Models");
    Data::Vector Textures = Data::Vector("Textures");
    Data::Vector Materials = Data::Vector("Materials");

private: //Element Types
    void LogElement();
    void AssetsElement();

public: //Functions
    Element(const int& GetID, int GetType = 0);
    void Render();

};

//############################## GUI ##############################//

class GUI
{
private: //Programs
    LOG Log = LOG();

private: //Varibles
    GLFWwindow* Window;
    int Width, Height;
    std::vector<Element*> SubWindow; 

private: //Gui Events
    void CreateNewSubWindow(const int& Type = 0);
    void DeleteSubWindow(const int& ID);

public: //Functions
    bool WindowShouldClose = false;
    GUI(GLFWwindow* GetWindow);
    void Render();
    ~GUI();

};