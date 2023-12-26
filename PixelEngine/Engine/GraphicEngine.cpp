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

        //Set Window Settings
        glfwWindowHint(GLFW_DECORATED, false);
        Log.INFO("Removed Top Bar");

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
        
        //Set Window Position
        glfwSetWindowPos(Window, (Mode->width - WindowSettings.Width)/2, (Mode->height - WindowSettings.Height)/2);
        Log.INFO("Center The Window");

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
    ImGui::Begin("Dockspace Window", &Dockspace, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground );
    ImGui::SetWindowPos(ImVec2(0,30));
    glfwGetWindowSize(Window, &Width, &Height);
    ImGui::SetWindowSize(ImVec2(Width, Height - 30));
    ImGuiID DockspaceID = ImGui::GetID("Dockspace");
    ImGui::DockSpace(DockspaceID, ImVec2(0,0), ImGuiDockNodeFlags_PassthruCentralNode);

    //Style TopBar
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12,0.23,0.23,1.0));

    //Create TopBar
    ImGui::Begin("TopBar", &Dockspace, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos(ImVec2(0,0));
        ImGui::SetWindowSize(ImVec2(Width, 30));
        //Create Add Sub Window BTN
        if(ImGui::Button("Add",ImVec2(30, 30))) {CreateNewSubWindow();};
        //Create Exit BTN
        ImGui::SetCursorPos(ImVec2(Width-30, 0));
        if(ImGui::Button("X", ImVec2(30, 30))) {WindowShouldClose = true; Log.MESSAGE("WindowShouldClose " + WindowShouldClose);};
    ImGui::End();

    //Pop TopBar Style
    ImGui::PopStyleColor();

    //Load Sub Windows
    for(int Count = 0; Count < SubWindow.size(); Count++){
        SubWindow[Count]->Render();
    }

    ImGui::End();

    //Pop Dockspace Style
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

void GUI::CreateNewSubWindow(){
    Element* NewWindow = new Element(SubWindow.size());
    SubWindow.push_back(NewWindow);
    Log.MESSAGE("Created New Window");
}

//############################## Elements ##############################//

Element::Element(const int& GetID, int GetType){
    ID = GetID;
    Type = GetType;
}

void Element::Render(){
    //Create Sub Window
    ImGui::Begin(("Window " + std::to_string(ID)).c_str());
        ImGui::Text(Log.GetLog().c_str());
    ImGui::End();
}
