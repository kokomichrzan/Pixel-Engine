#include "GraphicEngine.h"

GLFWwindow* GraphicEngine::CreateWindow()
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
    glfwSetWindowSizeLimits(Window, 1000, 900, GLFW_DONT_CARE, GLFW_DONT_CARE); //Set Window MinSize

    //Set Context
    glfwMakeContextCurrent(Window);

    //Set Glad
    gladLoadGL();
    glad_glViewport(0, 0, WindowSettings.Width, WindowSettings.Height);
    Log.INFO("Loaded GLAD");

    return Window;
    
}

void GraphicEngine::Events(GLFWwindow* Window){
    Resize(Window);
    Move(Window);

}

void GraphicEngine::Move(GLFWwindow* Window){
    glfwGetCursorPos(Window, &MouseX, &MouseY);
    glfwGetWindowPos(Window, &WindowLastX, &WindowLastY);
    if(((MouseY < 30 && MouseY > EventSize) || MoveLock) && !(ResizeTopLock || ResizeBottomLock || ResizeLeftLock || ResizeRightLock)){
        if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
            if(GetPoses) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
            GetPoses = false;
            MoveLock = true;
            glfwSetWindowPos(Window, WindowLastX + int(MouseX - MouseLastX), WindowLastY + int(MouseY - MouseLastY));
            glfwSetCursorPos(Window, MouseLastX, MouseLastY);
        }
        else {GetPoses = true; MoveLock= false;};
    }
}
    
void GraphicEngine::Resize(GLFWwindow* Window){
    //Get Data
    glfwGetCursorPos(Window, &MouseX, &MouseY);
    glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);
    glfwGetWindowPos(Window, &WindowLastX, &WindowLastY);

    if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && (( MouseX >= EventSize && MouseX <= WindowWidth - EventSize && MouseY >= EventSize && MouseY <= WindowHeight - EventSize) || (MoveElemet)) && !(ResizeTopLock || ResizeBottomLock || ResizeLeftLock || ResizeRightLock))
         MoveElemet = true;
    else MoveElemet = false;

    if(!MoveLock && !MoveElemet)
    {
        //Left
        if(((MouseX < EventSize && MouseY > 30 && (MouseY < (WindowHeight - EventSize))) || ResizeLeftLock) && !(ResizeTopLock || ResizeBottomLock || ResizeRightLock)) {
            //Resize
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(GetResize) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    GetResize = false;
                    ResizeLeftLock = true;
                    if((WindowWidth - (MouseX - MouseLastX)) >= 1000) {
                        glfwSetWindowPos(Window, int(WindowLastX + (MouseX - MouseLastX)), WindowLastY);
                        glfwSetWindowSize(Window, int(WindowWidth - (MouseX - MouseLastX)), WindowHeight);
                        glfwSetCursorPos(Window, MouseLastX, MouseLastY);
                    }
                } else {GetResize = true; ResizeLeftLock = false;};
            }

        //Right
        if(((MouseX > (WindowWidth - EventSize) && MouseY > 30 && (MouseY < (WindowHeight - EventSize))) || ResizeRightLock) && !(ResizeTopLock || ResizeBottomLock || ResizeLeftLock)){ 
            //Resize
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(GetResize) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    GetResize = false;
                    ResizeRightLock = true;
                    if(MouseX >= 1000) glfwSetWindowSize(Window, int(MouseX), WindowHeight);
                } else {GetResize = true; ResizeRightLock = false;};
        }

        //Top
        if(((MouseY < EventSize || ResizeTopLock)) && !(ResizeBottomLock || ResizeLeftLock || ResizeRightLock)){ 
            //Resize
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(GetResize) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    GetResize = false;
                    ResizeTopLock = true;
                    if((WindowHeight - (MouseY - MouseLastY)) >= 900) {
                        glfwSetWindowPos(Window, WindowLastX, int(WindowLastY + (MouseY - MouseLastY)));
                        glfwSetWindowSize(Window, WindowWidth, int(WindowHeight - (MouseY - MouseLastY)));
                        glfwSetCursorPos(Window, MouseLastX, MouseLastY);
                    }
                } else {GetResize = true; ResizeTopLock = false;};
        }

        //Bottom
        if((MouseY > (WindowHeight - EventSize) || ResizeBottomLock) && !(ResizeTopLock || ResizeLeftLock || ResizeRightLock)){ 
            //Resize
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(GetResize) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    GetResize = false;
                    ResizeBottomLock = true;
                    if(MouseY >= 900) glfwSetWindowSize(Window, WindowWidth, int(MouseY));
                } else {GetResize = true; ResizeBottomLock = false;};
        }
        
        //Check MinSize
        if(WindowWidth < 1000) glfwSetWindowSize(Window, 1000, WindowHeight);
        if(WindowHeight < 900) glfwSetWindowSize(Window, WindowWidth, 900);
        //SetGLad
        glViewport(0,0, WindowWidth, WindowHeight);

    }
}

void GraphicEngine::SaveWindowParams(GLFWwindow* Window){
    //Save Window Size
    glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);
    Data::Array WindowSettings = Data::Array("Settings", 5);
    WindowSettings.Read("Window");
    WindowSettings.Content[2] = std::to_string(WindowWidth);
    WindowSettings.Content[3] = std::to_string(WindowHeight);
    WindowSettings.Save("Window");
    Log.MESSAGE("Window Size Saved");

}