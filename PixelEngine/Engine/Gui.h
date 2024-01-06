#pragma once
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <utility>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "LOG.h"
#include "Data/Data.h"

//// GUI ////////////////////////////////////////////////////

class Element;

class GUI
{
private:
    GLFWwindow* Window;
    std::vector<Element*> SubWindows; 
    ImVec2 BTNSize = ImVec2(30, 30);
    const char* MinBTN = "-";
    const char* MaxBTN = "_";
    const char* ExitBTN = "X";
    int WindowWidth, WindowHeight;
    void CreateNewSubWindow(const unsigned int& Type = 0);
    void DeleteSubWindow(const unsigned int& ID);

public: 
    bool WindowShouldClose = false;
    GUI(GLFWwindow* WindowPtr);
    void Render();
    ~GUI();

};

//// Element ////////////////////////////////////////////////////

class Element{
public:
    unsigned int Type = 0;
    unsigned int ID = 0;
    bool RenderElement = true;

private:
    GLFWwindow* Window;
    std::string WindowTitle;

private:
    //SystemElement
    int WindowWidth, WindowHeight;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    //AssetsElement
    Data::Vector Models = Data::Vector("Models");
    Data::Vector Textures = Data::Vector("Textures");
    Data::Vector Materials = Data::Vector("Materials");

private:
    void LogElement();       //1
    void SystemElement();    //2
    void AssetsElement();    //3

public:
    Element(const unsigned int& GetID, GLFWwindow* Window, const unsigned int& GetType = 0);
    void Render();

};