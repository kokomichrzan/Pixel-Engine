#pragma once
//PCH
#include <pch.h>
//Programs
#include "LOG.h"
#include "Data.h"

//############################## Element ##############################//

class Element{
public: //Element Params
    unsigned int Type = 0;
    unsigned int ID = 0;
    bool RenderElement = true;

private: //Element Type Data
    //LogElement
    LOG Log = LOG();
    //AssetsElement
    Data::Vector Models = Data::Vector("Models");
    Data::Vector Textures = Data::Vector("Textures");
    Data::Vector Materials = Data::Vector("Materials");

private: //Element Types
    void LogElement();       //1
    void AssetsElement();    //2

public: //Functions
    Element(const unsigned int& GetID, const unsigned int& SetType = 0);
    void Render();

};

//############################## GUI ##############################//

class GUI
{
private: //Programs
    LOG Log = LOG();

private: //Varibles
    GLFWwindow* Window;
    int WindowWidth, WindowHeight;
    std::vector<Element*> SubWindows; 
    ImVec2 BTNSize = ImVec2(30, 30);
    const char* MinBTN = "-";
    const char* MaxBTN = "_";
    const char* ExitBTN = "X";

private: //Gui Events
    void CreateNewSubWindow(const unsigned int& Type = 0);
    void DeleteSubWindow(const unsigned int& ID);

public: //Functions
    bool WindowShouldClose = false;
    GUI(GLFWwindow* WindowPtr);
    void Render();
    ~GUI();

};