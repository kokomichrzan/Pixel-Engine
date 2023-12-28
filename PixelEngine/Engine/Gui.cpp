#include "Gui.h"

//############################## GUI ##############################//

GUI::GUI(GLFWwindow* WindowPtr)
{
    //Set Window Ptr
    Window = WindowPtr;

    // Setup Dear ImGui Context And Flags
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    //Set ImGui GLFW and GLAD
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //Load SubWindows
    Data::Vector GuiLoad = Data::Vector("Settings");
    GuiLoad.Read("Gui");
    for(int Count = 0; Count < GuiLoad.Content.size() - 1; Count += 2){
        Element* LoadSubWindow = new Element(std::stoi(GuiLoad.Content[Count]), std::stoi(GuiLoad.Content[Count + 1]));
        SubWindows.push_back(LoadSubWindow);

    }
    Log.INFO("GUI Loaded");

}

GUI::~GUI()
{
    //Save And Delete Sub Windows
    Data::Vector GuiSave = Data::Vector("Settings");
    for(int Count = 0; Count < SubWindows.size(); Count++){
        //Save Window ID and Type
        GuiSave.Add(std::to_string(SubWindows[Count]->ID));
        GuiSave.Add(std::to_string(SubWindows[Count]->Type));

        //Delete Sub Window
        delete SubWindows[Count];
        
    }
    GuiSave.Save("Gui");
    Log.INFO("GUI Saved");

    //Shut Down ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

void GUI::Render(){
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //Create MainWindow
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0));
    ImGui::Begin("Main Window", NULL, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground );
    
    //Create Dockspace
    glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);
    ImGui::SetWindowPos(ImVec2(0,30));
    ImGui::SetWindowSize(ImVec2(WindowWidth, WindowHeight - 30));
    ImGuiID DockspaceID = ImGui::GetID("Dockspace");
    ImGui::DockSpace(DockspaceID, ImVec2(0,0), ImGuiDockNodeFlags_PassthruCentralNode);

    //TopBar
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12,0.23,0.23,1.0));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 8));
    ImGui::BeginMainMenuBar();
        //File
        if(ImGui::BeginMenu("File")){
            if(ImGui::MenuItem("New")){};
            if(ImGui::MenuItem("Open")){};
            if(ImGui::MenuItem("Save")){};
            if(ImGui::MenuItem("Settings")){};
        ImGui::EndMenu();
        }
        //Window
        if(ImGui::BeginMenu("Window")){
            if(ImGui::MenuItem("New")){ CreateNewSubWindow(); };
            if(ImGui::MenuItem("Log")){ CreateNewSubWindow(1); };
            if(ImGui::MenuItem("Assets")){ CreateNewSubWindow(2); };
        ImGui::EndMenu();
        }

        //Title
        const int LeftOffset = ImGui::CalcTextSize("File").x + ImGui::CalcTextSize("Window").x;
        const int RightOffset = ImGui::CalcTextSize("Exit").x + ImGui::CalcTextSize("Min").x + ImGui::CalcTextSize("Max").x;
        ImGui::SetCursorPos(ImVec2((WindowWidth - LeftOffset - RightOffset - ImGui::CalcTextSize("Pixel Engine").x)/2 + LeftOffset, 0));
        ImGui::Text("Pixel Engine");

        //Window Events
        //Min
        ImGui::SetCursorPos(ImVec2(WindowWidth - (BTNSize.x * 3) - 12, 0));
        if(ImGui::Button(MinBTN, BTNSize)) { glfwIconifyWindow(Window); };
        //Max
        ImGui::SetCursorPos(ImVec2(WindowWidth -  (BTNSize.x * 2) - 8, 0));
        if(ImGui::Button(MaxBTN, BTNSize)) { if(!glfwGetWindowAttrib(Window, GLFW_MAXIMIZED)) glfwMaximizeWindow(Window);  
        else {glfwRestoreWindow(Window); glfwSetWindowSize(Window, 1000, 900);} };
        //Exit
        ImGui::SetCursorPos(ImVec2(WindowWidth - BTNSize.x - 4, 0));
        if(ImGui::Button(ExitBTN, BTNSize)) { WindowShouldClose = true; };
    ImGui::EndMainMenuBar();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    //Render Sub Windows
    for(int Count = 0; Count < SubWindows.size(); Count++){
        if(SubWindows[Count]->RenderElement) SubWindows[Count]->Render();
        else DeleteSubWindow(Count);

    }
    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();

    //Render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    GLFWwindow* BackUPContext = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(BackUPContext);

}

//Gui Events
void GUI::CreateNewSubWindow(const unsigned int& Type){
    //Create Unique ID
    unsigned int ID;
    bool Findet = false;
    while (!Findet)
    {
        //Set Seed And Get Random
        srand((unsigned) time(NULL));
        ID = rand();  

        //Chack if ID is unique
        Findet = true;
        for(int Count = 0; Count < SubWindows.size(); Count++)
        { 
            if(SubWindows[Count]->ID == ID) Findet = false;
        }
        if(!SubWindows.size()) Findet = true;

    }
    
    //Create New Window
    Element* NewWindow = new Element(ID, Type);
    SubWindows.push_back(NewWindow);
    Log.MESSAGE("Created New Sub Window with ID " + std::to_string(ID));

}

void GUI::DeleteSubWindow(const unsigned int& ID){
    Log.MESSAGE("Removed Sub Window with ID " + std::to_string(SubWindows[ID]->ID));
    delete SubWindows[ID];
    SubWindows.erase(std::next(SubWindows.begin(), ID));

}

//############################## Elements ##############################//

Element::Element(const unsigned int& GetID, const unsigned int& GetType){
    ID = GetID;
    Type = GetType;

}

void Element::Render(){
    //Create Window
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::Begin(("Window " + std::to_string(ID)).c_str(), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar);
    
    //Title Bar
    ImGui::BeginMenuBar();
        if(ImGui::BeginMenu("Type")){
            if(ImGui::MenuItem("None")) Type = 0;
            if(ImGui::MenuItem("Log")) Type = 1;
            if(ImGui::MenuItem("Assets")) Type = 2;
        ImGui::EndMenu();
        }
        if(ImGui::MenuItem("Exit")) RenderElement = false;
    ImGui::EndMenuBar();

    //Render Window Type
    switch (Type)
    {
        case 0: break; //Clear Window
        case 1: LogElement(); break; //Log Element
        case 2: AssetsElement(); break; //Assets Element
    }

    ImGui::End();
    ImGui::PopStyleColor();

}

//Elements Types

void Element::LogElement(){
    ImGui::Text(Log.GetLog().c_str());
    if(Log.CheckIfScrollDown())ImGui::SetScrollHereY(1.0f);

}

void Element::AssetsElement(){


}