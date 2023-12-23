#include "GraphicEngine.h"

namespace Window
{
    GLFWwindow* Create(const std::string WindowTitle){

        //Load Settings
        Settings WindowSettings = Settings();
        Data SettingsData = Data(5, "Settings");
        if(!SettingsData.Exist()){
            SettingsData.Add(0, std::to_string(WindowSettings.FullScreen));
            SettingsData.Add(1, std::to_string(WindowSettings.AutoResolution));
            SettingsData.Add(2, std::to_string(WindowSettings.Width));
            SettingsData.Add(3, std::to_string(WindowSettings.Height));
            SettingsData.Add(4, std::to_string(WindowSettings.RefreshRate));

            SettingsData.Save();

        }else{
            WindowSettings.FullScreen = std::stoi(SettingsData.Content[0]);
            WindowSettings.AutoResolution = std::stoi(SettingsData.Content[1]);
            WindowSettings.Width = std::stoi(SettingsData.Content[2]);
            WindowSettings.Height = std::stoi(SettingsData.Content[3]);
            WindowSettings.RefreshRate = std::stoi(SettingsData.Content[4]);

        }

        //Init Window
        glfwInit();

        GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);

        //Refresh Rate
        if(WindowSettings.RefreshRate == 0) glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate);
        else glfwWindowHint(GLFW_REFRESH_RATE, WindowSettings.RefreshRate);
        
        // //Set Hints
        glfwWindowHint(GLFW_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //Set Window Settings
        glfwWindowHint(GLFW_DECORATED, false);

        //Set Resolution
        if(WindowSettings.AutoResolution){
            WindowSettings.Width = Mode->height;
            WindowSettings.Height = Mode->height;
        }

        //Create Window
        GLFWwindow* Window;
        if(WindowSettings.FullScreen)
        Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), Monitor, NULL);
        else
        Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), NULL, NULL);

        
        glfwSetWindowPos(Window, (Mode->width - WindowSettings.Width)/2, (Mode->height - WindowSettings.Height)/2);

        //Set Glad
        gladLoadGL();
        glViewport(0, 0, WindowSettings.Width, WindowSettings.Height);
        
        //Return Window
        return Window;
    }
    
} // namespace Window

