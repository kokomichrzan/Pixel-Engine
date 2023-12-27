#include "GraphicEngine.h"

LOG Log = LOG();

namespace GraphicEngine
{
    GLFWwindow* Create(const std::string& WindowTitle){

        //Load Settings
        Settings WindowSettings = Settings();
        Data::Array SettingsData = Data::Array("Settings", 5);
        SettingsData.Read("Window");
        if(!SettingsData.Exist("Window")){
            SettingsData.Content[0] = std::to_string(WindowSettings.FullScreen);
            SettingsData.Content[1] = std::to_string(WindowSettings.AutoResolution);
            SettingsData.Content[2] = std::to_string(WindowSettings.Width);
            SettingsData.Content[3] = std::to_string(WindowSettings.Height);
            SettingsData.Content[4] = std::to_string(WindowSettings.RefreshRate);

            SettingsData.Save("Window");
            Log.INFO("Create Window Settings");

        }else{
            WindowSettings.FullScreen =     std::stoi(SettingsData.Content[0]);
            WindowSettings.AutoResolution = std::stoi(SettingsData.Content[1]);
            WindowSettings.Width =          std::stoi(SettingsData.Content[2]);
            WindowSettings.Height =         std::stoi(SettingsData.Content[3]);
            WindowSettings.RefreshRate =    std::stoi(SettingsData.Content[4]);

            Log.INFO("Loaded Window Settings");
        }

        //Init Window
        glfwInit();
        Log.INFO("GLFW Initialized");

        //Get Window Params
        GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);

        //Refresh Rate
        if(WindowSettings.RefreshRate == 0) {glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate); Log.INFO("Setted Refresh Rate to " + Mode->refreshRate);}
        else{ glfwWindowHint(GLFW_REFRESH_RATE, WindowSettings.RefreshRate); Log.INFO("Setted Refresh Rate to " + WindowSettings.RefreshRate);}
        
        //Set Hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        Log.INFO("Seted Window Glad Hints");

        //Remove TopBar
        glfwWindowHint(GLFW_DECORATED, false);
        Log.INFO("Remove TopBar");

        //Set Resolution
        if(WindowSettings.AutoResolution){
            WindowSettings.Width = Mode->width;
            WindowSettings.Height = Mode->height;
        }
        Log.INFO("Seted Resolution on " + std::to_string(WindowSettings.Width) + " x " + std::to_string(WindowSettings.Height));

        //Create Window
        GLFWwindow* Window;
        if(WindowSettings.FullScreen)
        {
            Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), Monitor, NULL);
            Log.INFO("Create Full Screen Window");
        }
        else
        {
            Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), NULL, NULL);
            Log.INFO("Create Window");
        }

        //Check If Window Created
        if(!Window){
            Log.WARNING("Can not Create Window");
        }
        
        //Set Prop
        glfwSetWindowPos(Window, (Mode->width - WindowSettings.Width)/2, (Mode->height - WindowSettings.Height)/2); //Set Window Position
        glfwSetWindowSizeLimits(Window, 1000, 700, GLFW_DONT_CARE, GLFW_DONT_CARE); //Set Window MinSize
        Log.INFO("Seted Windo Prop");

        //Set Context
        glfwMakeContextCurrent(Window);

        //Set Glad
        gladLoadGL();
        glad_glViewport(0, 0, WindowSettings.Width, WindowSettings.Height);
        Log.INFO("Loaded GLAD");
        
        //Return Window
        return Window;
    }
    
} // namespace Window

//############################## GUI ##############################//

GUI::GUI(GLFWwindow* GetWindow)
{
    //Get Window Ptr
    Window = GetWindow;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    Log.INFO("Loaded ImGui Flags");

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    Log.INFO("Set ImGui Style");

    //Init IMGUI
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    Log.INFO("Init Glad and GLFW for ImGUi");

    //Load SubWindows
    Data::Vector GuiLoad = Data::Vector("Settings");
    GuiLoad.Read("Gui");
    for(int Count = 0; Count < GuiLoad.Content.size() - 1; Count += 2){
        Element* LoadSubWindow = new Element(std::stoi(GuiLoad.Content[Count]), std::stoi(GuiLoad.Content[Count + 1]));
        SubWindow.push_back(LoadSubWindow);
    }
    Log.INFO("GUI Loaded");

}

void GUI::Render(){
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //Set Dockspace Style
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0));

    //Create Dockspace
    ImGui::Begin("Dockspace Window", NULL, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground );
    ImGui::SetWindowPos(ImVec2(0,30));
    glfwGetWindowSize(Window, &Width, &Height);
    ImGui::SetWindowSize(ImVec2(Width, Height - 30));
    ImGuiID DockspaceID = ImGui::GetID("Dockspace");
    ImGui::DockSpace(DockspaceID, ImVec2(0,0), ImGuiDockNodeFlags_PassthruCentralNode);

    //TopBar
    //Style TopBar
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12,0.23,0.23,1.0));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 8));
    ImGui::BeginMainMenuBar();
    //     //Icon
    //     // ImGui::Image();
        //Evemt BTN
    //  //File
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
        ImGui::SetCursorPos(ImVec2((Width - LeftOffset - RightOffset - ImGui::CalcTextSize("Pixel Engine").x)/2 + LeftOffset,0));
        ImGui::Text("Pixel Engine");

        //Window BTNs
        const char* Min = "-";
        const char* Max = "_";
        const char* Exit = "X";
        ImVec2 BTNSize = ImVec2(30, 30);
        //Min
        ImGui::SetCursorPos(ImVec2(Width - (BTNSize.x * 3) - 12, 0));
        if(ImGui::Button(Min, BTNSize)) 
        { glfwIconifyWindow(Window); };
        //Max
        ImGui::SetCursorPos(ImVec2(Width -  (BTNSize.x * 2) - 8, 0));
        if(ImGui::Button(Max, BTNSize)) 
        { if(!glfwGetWindowAttrib(Window, GLFW_MAXIMIZED)) glfwMaximizeWindow(Window);  
        else glfwRestoreWindow(Window); };
        //Exit
        ImGui::SetCursorPos(ImVec2(Width - BTNSize.x - 4, 0));
        if(ImGui::Button(Exit, BTNSize)) 
        { WindowShouldClose = true; };
    ImGui::EndMainMenuBar();

    //Pop TopBar Style
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    //Load Sub Windows
    for(int Count = 0; Count < SubWindow.size(); Count++){
        if(SubWindow[Count]->RenderElement)SubWindow[Count]->Render();
        else DeleteSubWindow(Count);
    }

    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();

    //Render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
}

GUI::~GUI()
{
    //Save And Delete Sub Windows
    Data::Vector GuiSave = Data::Vector("Settings");
    for(int Count = 0; Count < SubWindow.size(); Count++){
        GuiSave.Add(std::to_string(SubWindow[Count]->ID));
        GuiSave.Add(std::to_string(SubWindow[Count]->Type));
        Log.INFO("Removed Window " + Count);

        //Delete Sub Window
        delete SubWindow[Count];
    }
    GuiSave.Save("Gui");
    Log.INFO("GUI Saved");

    //Shut Down ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

//############################## GUI Events ##############################//

void GUI::CreateNewSubWindow(const int& Type){
    //Create Unique ID
    int IDW;
    bool Findet = false;
    while (!Findet)
    {
        IDW = rand();
        if(!SubWindow.size()) Findet = true;

        //Chack if IDW is used
        for(int Count = 0; Count < SubWindow.size(); Count++)
        {
            Findet = true;
            if(SubWindow[Count]->ID == IDW) Findet = false;
        }
    }
    
    //Create New Window
    Element* NewWindow = new Element(IDW, Type);
    SubWindow.push_back(NewWindow);
    Log.MESSAGE("Created New Window");
}

void GUI::DeleteSubWindow(const int& ID){
    delete SubWindow[ID];
    SubWindow.erase(std::next(SubWindow.begin(), ID));
    Log.MESSAGE("Removed Sub Window");
}

//############################## Elements ##############################//

Element::Element(const int& GetID, int GetType){
    ID = GetID;
    Type = GetType;
}

void Element::Render(){
    //Set Style
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    //Start Window
    ImGui::Begin(("Window " + std::to_string(ID)).c_str(), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar);
    
    //Title Bar
    ImGui::BeginMenuBar();
        if(ImGui::BeginMenu("Type")){
            if(ImGui::MenuItem("None"))
            {
                Type = 0;
            }
            if(ImGui::MenuItem("LOG"))
            {
                Type = 1;
            }
        ImGui::EndMenu();
        }
        if(ImGui::MenuItem("Exit")){
            RenderElement = false;
        }

    ImGui::EndMenuBar();

    //Render Window Type
    switch (Type)
    {
        case 0: break; //Clear Window
        case 1: LOG(); break; //LOG Window
        case 2: Assets(); break; //Assets Window
    }
    ImGui::End();
    ImGui::PopStyleColor();
}

//############################## Render Type ##############################//

void Element::LOG(){
    //Render Log
    ImGui::Text(Log.GetLog().c_str());

}

void Element::Assets(){

}