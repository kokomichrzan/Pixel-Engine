#pragma once
#include <pch.h>
#include "Window.h"
#include "../Scripts/LOG.h"

namespace PE {

    //// GUI ////////////////////////////////////////////////////

    class Element;

    class GUI
    {
    private:
        Window *Window;
        std::vector<Element*> SubWindows;
        int WindowWidth, WindowHeight;
        void CreateNewSubWindow(const unsigned int& Type = 0);
        void DeleteSubWindow(const unsigned int& ID);

    public:
        bool WindowShouldClose = false;
        GUI(PE::Window *Window);
        void Render();
        ~GUI();

    };

    //// Element ////////////////////////////////////////////////////

    class Element {
    public:
        unsigned int Type = 0;
        unsigned int ID = 0;
        bool RenderElement = true;

    private:
        PE::Window *Window;
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
        Element(const unsigned int& GetID, PE::Window *Window, const unsigned int& GetType = 0);
        void Render();

    };
}