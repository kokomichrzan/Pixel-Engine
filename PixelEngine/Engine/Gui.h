#pragma once
//PCH
#include <pch.h>
//Programs
#include "LOG.h"
#include "Data.h"

//############################## GUI ##############################//

class Element;

class GUI
{
private: //Programs
    LOG Log = LOG();

private: //Varibles
    GLFWwindow* Window;
    std::vector<Element*> SubWindows; 
    ImVec2 BTNSize = ImVec2(30, 30);
    const char* MinBTN = "-";
    const char* MaxBTN = "_";
    const char* ExitBTN = "X";
    int WindowWidth, WindowHeight;

private: //Gui Events
    void CreateNewSubWindow(const unsigned int& Type = 0);
    void DeleteSubWindow(const unsigned int& ID);

public: //Functions
    bool WindowShouldClose = false;
    GUI(GLFWwindow* WindowPtr);
    void Render();
    ~GUI();

};

//############################## Element ##############################//

class Element{
public: //Element Params
    unsigned int Type = 0;
    unsigned int ID = 0;
    bool RenderElement = true;
    GLFWwindow* Window;

private: //Element Type Data
    //LogElement
    LOG Log = LOG();
    //SystemElement
    int WindowWidth, WindowHeight;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    //AssetsElement
    Data::Vector Models = Data::Vector("Models");
    Data::Vector Textures = Data::Vector("Textures");
    Data::Vector Materials = Data::Vector("Materials");

private: //Element Types
    void LogElement();       //1
    void SystemElement();    //2
    void AssetsElement();    //3

public: //Functions
    Element(const unsigned int& GetID, GLFWwindow* Window, const unsigned int& GetType = 0);
    void Render();

};