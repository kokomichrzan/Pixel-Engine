#include "GraphicEngine.h"

GLFWwindow* GraphicEngine::CreateWindow(const std::string& WindowTitle)
{
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

    //Get Window Params
    GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);

    //Refresh Rate
    if(WindowSettings.RefreshRate == 0) {glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate); Log.INFO("Setted Refresh Rate to " + std::to_string(Mode->refreshRate));}
    else{ glfwWindowHint(GLFW_REFRESH_RATE, WindowSettings.RefreshRate); Log.INFO("Setted Refresh Rate to " + std::to_string(WindowSettings.RefreshRate));}
    
    //Set Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Remove TopBar
    glfwWindowHint(GLFW_DECORATED, false);

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

    //Set Context
    glfwMakeContextCurrent(Window);

    //Set Glad
    gladLoadGL();
    glad_glViewport(0, 0, WindowSettings.Width, WindowSettings.Height);
    Log.INFO("Loaded GLAD");

    return Window;
    
}

void GraphicEngine::Events(GLFWwindow* Window){

    Move(Window);

}

void GraphicEngine::Move(GLFWwindow* Window){
    //Move
    glfwGetCursorPos(Window, &MouseX, &MouseY);
    if((glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && MouseY < 50){
        if(GetPoses) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
        glfwGetWindowPos(Window, &WindowLastX, &WindowLastY);
        GetPoses = false;
        glfwSetWindowPos(Window, WindowLastX + int(MouseX - MouseLastX), WindowLastY + int(MouseY - MouseLastY));
        glfwSetCursorPos(Window, MouseLastX, MouseLastY);
    }
    else GetPoses = true;
}
    
