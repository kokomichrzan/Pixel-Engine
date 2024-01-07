#include "pch.h"
#include "Gui.h"

namespace PE {

    //############################## GUI ##############################//

    GUI::GUI(PE::Window *Window)
        :Window(Window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(Window->HWindow, true);
        ImGui_ImplOpenGL3_Init("#version 460");

        Data::Vector GuiLoad = Data::Vector("Settings");
        GuiLoad.Read("Gui");
        for (int Count = 0; Count < GuiLoad.Content.size() - 1; Count += 2) {
            Element* LoadSubWindow = new Element(std::stoi(GuiLoad.Content[Count]), Window, std::stoi(GuiLoad.Content[Count + 1]));
            SubWindows.push_back(LoadSubWindow);

        }
        LOG::MESSAGE("GUI Loaded");
    }

    GUI::~GUI()
    {
        Data::Vector GuiSave = Data::Vector("Settings");
        for (int Count = 0; Count < SubWindows.size(); Count++) {
            //Save Window ID and Type
            GuiSave.Add(std::to_string(SubWindows[Count]->ID));
            GuiSave.Add(std::to_string(SubWindows[Count]->Type));

            delete SubWindows[Count];

        }
        GuiSave.Save("Gui");
        LOG::MESSAGE("GUI Saved");

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

    }

    void GUI::Render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
        ImGui::Begin("Main Window", NULL, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

        glfwGetWindowSize(Window->HWindow, &WindowWidth, &WindowHeight);
        ImGui::SetWindowPos(ImVec2(0, 30));
        ImGui::SetWindowSize(ImVec2(WindowWidth, WindowHeight - 30));
        ImGuiID DockspaceID = ImGui::GetID("Dockspace");
        ImGui::DockSpace(DockspaceID, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

        //TopBar
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12, 0.23, 0.23, 1.0));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 8));
        ImGui::BeginMainMenuBar();
        //File
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New")) {};
            if (ImGui::MenuItem("Open")) {};
            if (ImGui::MenuItem("Save")) {};
            if (ImGui::MenuItem("Settings")) {};
            ImGui::EndMenu();
        }
        //Window
        if (ImGui::BeginMenu("Window")) {
            if (ImGui::MenuItem("New")) { CreateNewSubWindow(); };
            if (ImGui::MenuItem("Log")) { CreateNewSubWindow(1); };
            if (ImGui::MenuItem("System")) { CreateNewSubWindow(2); };
            if (ImGui::MenuItem("Assets")) { CreateNewSubWindow(3); };
            ImGui::EndMenu();
        }

        //Title
        const int LeftOffset = ImGui::CalcTextSize("File").x + ImGui::CalcTextSize("Window").x;
        ImGui::SetCursorPos(ImVec2((WindowWidth - LeftOffset - ImGui::CalcTextSize("Pixel Engine").x) / 2 + LeftOffset, 0));
        ImGui::Text("Pixel Engine");
        ImGui::EndMainMenuBar();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();

        //Render Sub Windows
        for (int Count = 0; Count < SubWindows.size(); Count++) {
            if (SubWindows[Count]->RenderElement) SubWindows[Count]->Render();
            else DeleteSubWindow(Count);

        }
        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        GLFWwindow* BackUPContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(BackUPContext);
    }

    void GUI::CreateNewSubWindow(const unsigned int& Type) {
        unsigned int ID;
        bool Findet = false;
        while (!Findet)
        {
            srand((unsigned)time(NULL));
            ID = rand();
            Findet = true;
            for (int Count = 0; Count < SubWindows.size(); Count++) if (SubWindows[Count]->ID == ID) Findet = false;
            if (!SubWindows.size()) Findet = true;
        }

        Element* NewWindow = new Element(ID, Window, Type);
        SubWindows.push_back(NewWindow);
        LOG::INFO("Created New Sub Window with ID " + std::to_string(ID));
    }

    void GUI::DeleteSubWindow(const unsigned int& ID) {
        LOG::INFO("Removed Sub Window with ID " + std::to_string(SubWindows[ID]->ID));
        delete SubWindows[ID];
        SubWindows.erase(std::next(SubWindows.begin(), ID));
    }

    //############################## Elements ##############################//

    Element::Element(const unsigned int& GetID, PE::Window *Window, const unsigned int& GetType)
        :ID(GetID), Window(Window), Type(GetType), WindowTitle("Window " + std::to_string(ID)) {}

    void Element::Render() {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
        ImGui::Begin(WindowTitle.c_str(), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar);
        //Title Bar
        ImGui::BeginMenuBar();
        if (ImGui::BeginMenu("Type")) {
            if (ImGui::MenuItem("None")) Type = 0;
            if (ImGui::MenuItem("Log")) Type = 1;
            if (ImGui::MenuItem("System")) Type = 2;
            if (ImGui::MenuItem("Assets")) Type = 3;
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Exit")) RenderElement = false;
        ImGui::EndMenuBar();

        switch (Type)
        {
        case 0: break; //Clear Window
        case 1: LogElement(); break; //Log Element
        case 2: SystemElement(); break; //System Element
        case 3: AssetsElement(); break; //System Element
        };

        ImGui::End();
        ImGui::PopStyleColor();

    }

    //Elements Types

    void Element::LogElement() {
        for (std::pair<const ImVec4&, const std::string&> Line : LOG::LogData) {
            ImGui::PushStyleColor(ImGuiCol_Text, Line.first);
            ImGui::Text(Line.second.c_str());
            ImGui::PopStyleColor();
        };

        if (LOG::ScrollDown) {
            ImGui::SetScrollHereY(1.0f);
            LOG::ScrollDown = false;
        }
    }

    void Element::SystemElement() {
        //Resolution
        glfwGetWindowSize(Window->HWindow, &WindowWidth, &WindowHeight);
        std::string Resolution = "Resolution: " + std::to_string(WindowWidth) + " x " + std::to_string(WindowHeight);
        ImGui::Text(Resolution.c_str());

        //get microseconds
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration μsDuration = end - start;
        std::chrono::microseconds qs = std::chrono::duration_cast<std::chrono::microseconds>(μsDuration);
        start = std::chrono::high_resolution_clock::now();

        //Print microsecends
        std::string qsTime = "Qs: " + std::to_string(qs.count());
        ImGui::Text(qsTime.c_str());
        //Print ms
        std::string msText = "Ms: " + std::to_string(qs.count() / 1000);
        ImGui::Text(msText.c_str());
        //Print FPS
        int FPS = 1000000 / qs.count();
        std::string FPSText = "FPS: " + std::to_string(FPS);
        ImGui::Text(FPSText.c_str());
    }

    void Element::AssetsElement() {

    }
}