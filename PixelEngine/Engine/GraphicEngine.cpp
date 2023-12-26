#include "GraphicEngine.h"

LOG Log = LOG();

namespace GraphicEngine
{
    GLFWwindow* Create(const std::string WindowTitle){

        //Load Settings
        Settings WindowSettings = Settings();
        Data::Array SettingsData = Data::Array("Data", 5);
        SettingsData.Read("Settings");
        if(!SettingsData.Exist("Settings")){
            SettingsData.Content[0] = std::to_string(WindowSettings.FullScreen);
            SettingsData.Content[1] = std::to_string(WindowSettings.AutoResolution);
            SettingsData.Content[2] = std::to_string(WindowSettings.Width);
            SettingsData.Content[3] = std::to_string(WindowSettings.Height);
            SettingsData.Content[4] = std::to_string(WindowSettings.RefreshRate);

            SettingsData.Save("Settings");
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

        GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);

        //Refresh Rate
        if(WindowSettings.RefreshRate == 0) {glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate); Log.INFO("Setted Refresh Rate to " + Mode->refreshRate);}
        else{ glfwWindowHint(GLFW_REFRESH_RATE, WindowSettings.RefreshRate); Log.INFO("Setted Refresh Rate to " + WindowSettings.RefreshRate);}
        
        
        // //Set Hints
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
        {Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), Monitor, NULL);
        Log.INFO("Create Full Screen Window");}
        else
        {Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), NULL, NULL);
        Log.INFO("Create Window");}
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

}

void GUI::Render(){
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //GUI
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0));
    ImGui::Begin("Dockspace Window", &Dockspace, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground );
    ImGui::SetWindowPos(ImVec2(0,30));
    glfwGetWindowSize(Window, &Width, &Height);
    ImGui::SetWindowSize(ImVec2(Width, Height - 30));

    ImGuiID DockspaceID = ImGui::GetID("Dockspace");
    ImGui::DockSpace(DockspaceID, ImVec2(0,0), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12,0.23,0.23,1.0));
    ImGui::Begin("TopBar", &Dockspace, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(0,0));
    ImGui::SetWindowSize(ImVec2(Width, 30));
    if(ImGui::Button("Add",ImVec2(30, 30))) {Add();};
    ImGui::SetCursorPos(ImVec2(Width-40, 0));
    if(ImGui::Button("Exit", ImVec2(40, 30))) {WindowShouldClose = true; Log.MESSAGE("WindowShouldClose " + WindowShouldClose);};
    ImGui::End();
    ImGui::PopStyleColor();

    for(int Count = 0; Count < Windows.size(); Count++){
        Windows[Count]->Render();
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
    for(int Count = 0; Count < Windows.size(); Count++){
        Log.INFO("Removed Window " + Count);
        delete Windows[Count];
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::Add(){
    Elements* Element = new Elements(Windows.size());
    Windows.push_back(Element);
    Log.MESSAGE("Created New Window");
}

GUI::Elements::Elements(int GetID){
    ID = GetID;
}

//############################## Elements ##############################//

void GUI::Elements::Render(){
    ImGui::Begin(("Window " + std::to_string(ID)).c_str());
    ImGui::Text(Log.GETLOG().c_str());
    ImGui::End();
}
