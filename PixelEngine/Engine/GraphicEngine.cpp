#include "GraphicEngine.h"

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

        }else{
            WindowSettings.FullScreen =     std::stoi(SettingsData.Content[0]);
            WindowSettings.AutoResolution = std::stoi(SettingsData.Content[1]);
            WindowSettings.Width =          std::stoi(SettingsData.Content[2]);
            WindowSettings.Height =         std::stoi(SettingsData.Content[3]);
            WindowSettings.RefreshRate =    std::stoi(SettingsData.Content[4]);

        }

        //Init Window
        glfwInit();

        GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);

        //Refresh Rate
        if(WindowSettings.RefreshRate == 0) glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate);
        else glfwWindowHint(GLFW_REFRESH_RATE, WindowSettings.RefreshRate);
        
        // //Set Hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //Set Window Settings
        glfwWindowHint(GLFW_DECORATED, false);

        //Set Resolution
        if(WindowSettings.AutoResolution){
            WindowSettings.Width = Mode->width;
            WindowSettings.Height = Mode->height;
        }

        //Create Window
        GLFWwindow* Window;
        if(WindowSettings.FullScreen)
        Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), Monitor, NULL);
        else
        Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), NULL, NULL);
        if(!Window){
            LOG("Window is not created");
        }
        
        //Set Window Position
        glfwSetWindowPos(Window, (Mode->width - WindowSettings.Width)/2, (Mode->height - WindowSettings.Height)/2);

        //Set Context
        glfwMakeContextCurrent(Window);

        //Set Glad
        gladLoadGL();
        glad_glViewport(0, 0, WindowSettings.Width, WindowSettings.Height);
        
        //Return Window
        return Window;
    }
    
} // namespace Window

//############################## GUI ##############################//

GUI::GUI(GLFWwindow* Window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    RefreshRate = &(io.Framerate);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    //Init IMGUI
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

}

void GUI::Render(){
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //GUI
    ImGui::Begin("System Info");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / *RefreshRate, *RefreshRate);
    ImGui::End();

    //Render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
