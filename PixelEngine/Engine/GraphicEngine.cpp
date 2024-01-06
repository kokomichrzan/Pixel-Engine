#include "GraphicEngine.h"

GLFWwindow* GraphicEngine::CreateWindow()
{
    Settings WindowSettings = Settings();
    Data::Array SettingsData = Data::Array("Settings", 4);
    SettingsData.Read("Window");
    if(!SettingsData.Exist("Window")){
        SettingsData.Content[0] = std::to_string(WindowSettings.FullScreen);
        SettingsData.Content[1] = std::to_string(WindowSettings.Width);
        SettingsData.Content[2] = std::to_string(WindowSettings.Height);
        SettingsData.Content[3] = std::to_string(WindowSettings.RefreshRate);

        SettingsData.Save("Window");
        Log.MESSAGE("Create Window Settings");

    }else{
        WindowSettings.FullScreen =     std::stoi(SettingsData.Content[0]);
        WindowSettings.Width =          std::stoi(SettingsData.Content[1]);
        WindowSettings.Height =         std::stoi(SettingsData.Content[2]);
        WindowSettings.RefreshRate =    std::stoi(SettingsData.Content[3]);

        Log.MESSAGE("Loaded Window Settings");
    }

    glfwInit();

    FullScreen = WindowSettings.FullScreen;
    RefreshRate = WindowSettings.RefreshRate;

    GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);

    if(WindowSettings.RefreshRate == 0) {glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate); 
    Log.MESSAGE("Setted Refresh Rate to " + std::to_string(Mode->refreshRate));}
    else{ glfwWindowHint(GLFW_REFRESH_RATE, WindowSettings.RefreshRate); 
    Log.MESSAGE("Setted Refresh Rate to " + std::to_string(WindowSettings.RefreshRate));
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, false);

    if(WindowSettings.FullScreen){
        WindowSettings.Width = Mode->width;
        WindowSettings.Height = Mode->height;
    }
    if (WindowSettings.Width < 1000) WindowSettings.Width = 1000;
    if (WindowSettings.Height < 900) WindowSettings.Height = 900;
    Log.MESSAGE("Seted Resolution on " + std::to_string(WindowSettings.Width) + " x " + std::to_string(WindowSettings.Height));

    GLFWwindow* Window;
    if(WindowSettings.FullScreen)
    {
        Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), Monitor, NULL);
        Log.MESSAGE("Create Full Screen Window");
    }
    else
    {
        Window = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), NULL, NULL);
        Log.MESSAGE("Create Window");
    }
    if(!Window) Log.WARNING("Can not Create Window");
    
    glfwSetWindowPos(Window, (Mode->width - WindowSettings.Width)/2, (Mode->height - WindowSettings.Height)/2); //Set Window Position
    glfwSetWindowSizeLimits(Window, 1000, 900, GLFW_DONT_CARE, GLFW_DONT_CARE); //Set Window MinSize
    glfwMakeContextCurrent(Window);

    gladLoadGL();
    glad_glViewport(0, 0, WindowSettings.Width, WindowSettings.Height);
    Log.MESSAGE("Loaded GLAD");

    Log.INFO("Window Created");
    return Window;
}

void GraphicEngine::Events(GLFWwindow* Window){
    Resize(Window);
    Move(Window);
    ToggleFullscreen(Window);
}

void GraphicEngine::Move(GLFWwindow* Window){
    //Get Positions
    glfwGetCursorPos(Window, &MouseX, &MouseY);
    glfwGetWindowPos(Window, &WindowLastX, &WindowLastY);

    if(((MouseY < EventMoveSize && MouseY > EventResizeSize) || MoveEvent) && //Cursor on TopBar or Is Currently Moving
    !(ResizeTopLock || ResizeBottomLock || ResizeLeftLock || ResizeRightLock) && //Is Currently not Resizing
    !FullScreen){ //Check if is not fullscreen
        if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){ //Is Cursor Down
            //Get First Mouse Position
            if(MoveGetEvent) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
            MoveGetEvent = false;
            //Set Program is currently Moving
            MoveEvent = true; 
            //Set New Window Pos
            glfwSetWindowPos(Window, WindowLastX + int(MouseX - MouseLastX), WindowLastY + int(MouseY - MouseLastY));
            //Set Cursor to last Position on App Screen
            glfwSetCursorPos(Window, MouseLastX, MouseLastY);

        }
        else {MoveGetEvent = true; MoveEvent= false;}; //Set Program stops moving screen

    }

}
    
void GraphicEngine::Resize(GLFWwindow* Window){
    glfwGetCursorPos(Window, &MouseX, &MouseY);
    glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);
    glfwGetWindowPos(Window, &WindowLastX, &WindowLastY);

    //Check if User is pressing key inside window
    if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
    (( MouseX >= EventResizeSize && MouseX <= WindowWidth - EventResizeSize && 
    MouseY >= EventResizeSize && MouseY <= WindowHeight - EventResizeSize) || (MouseInSideLock)) &&
    !(ResizeTopLock || ResizeBottomLock || ResizeLeftLock || ResizeRightLock))

    MouseInSideLock = true;
    else MouseInSideLock = false;

    if(!MoveEvent && !MouseInSideLock && !FullScreen)
    {
        //Left Resize
        if(((MouseX < EventResizeSize &&
        MouseY > 30 && (MouseY < (WindowHeight - EventResizeSize))) || ResizeLeftLock) &&
        !(ResizeTopLock || ResizeBottomLock || ResizeRightLock)) {
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(ResizeGetEvent) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    ResizeGetEvent = false;
                    ResizeLeftLock = true;
                    if((WindowWidth - (MouseX - MouseLastX)) >= 1000) { 
                        glfwSetWindowPos(Window, int(WindowLastX + (MouseX - MouseLastX)), WindowLastY); 
                        glfwSetWindowSize(Window, int(WindowWidth - (MouseX - MouseLastX)), WindowHeight);
                        glfwSetCursorPos(Window, MouseLastX, MouseLastY);
                    }
                } else {ResizeGetEvent = true; ResizeLeftLock = false;};
            }

        //Right Resize
        if(((MouseX > (WindowWidth - EventResizeSize) &&  
        MouseY > 30 && (MouseY < (WindowHeight - EventResizeSize))) || ResizeRightLock) && 
        !(ResizeTopLock || ResizeBottomLock || ResizeLeftLock)){ 
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(ResizeGetEvent) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    ResizeGetEvent = false;
                    ResizeRightLock = true;
                    if(MouseX >= 1000) glfwSetWindowSize(Window, int(MouseX), WindowHeight);
                } else {ResizeGetEvent = true; ResizeRightLock = false;};
        }

        //Top Resize
        if(((MouseY < EventResizeSize || ResizeTopLock)) &&
        !(ResizeBottomLock || ResizeLeftLock || ResizeRightLock)){
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(ResizeGetEvent) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    ResizeGetEvent = false;
                    ResizeTopLock = true;
                    if((WindowHeight - (MouseY - MouseLastY)) >= 900) {
                        glfwSetWindowPos(Window, WindowLastX, int(WindowLastY + (MouseY - MouseLastY)));
                        glfwSetWindowSize(Window, WindowWidth, int(WindowHeight - (MouseY - MouseLastY)));
                        glfwSetCursorPos(Window, MouseLastX, MouseLastY);
                    }
                } else {ResizeGetEvent = true; ResizeTopLock = false;};
        }

        //Bottom Resize
        if((MouseY > (WindowHeight - EventResizeSize) || ResizeBottomLock) &&
        !(ResizeTopLock || ResizeLeftLock || ResizeRightLock)){
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if(ResizeGetEvent) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    ResizeGetEvent = false;
                    ResizeBottomLock = true;
                    if(MouseY >= 900) glfwSetWindowSize(Window, WindowWidth, int(MouseY));
                } else {ResizeGetEvent = true; ResizeBottomLock = false;};
        }
        
        glViewport(0,0, WindowWidth, WindowHeight);
    }
}

void GraphicEngine::ToggleFullscreen(GLFWwindow* Window){
    if(glfwGetKey(Window, GLFW_KEY_F11) == GLFW_PRESS){
        if(!F11Pressed){ 
            F11Pressed = true;
            FullScreen = !FullScreen;
            GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);
            if(FullScreen){
                glfwSetWindowMonitor(Window, Monitor, 0, 0, Mode->width, Mode->height, RefreshRate); 
            }else{
                WindowWidth = 1000;
                WindowHeight = 900;
                glfwSetWindowMonitor(Window, NULL, (Mode->width - WindowWidth)/2, (Mode->height - WindowHeight)/2, WindowWidth, WindowHeight, RefreshRate); 
            }
        }
    }else F11Pressed = false;
}

void GraphicEngine::SaveWindowParams(GLFWwindow* Window){
    glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);
    Data::Array WindowSettings = Data::Array("Settings", 4);
    WindowSettings.Read("Window");
    WindowSettings.Content[0] = std::to_string(FullScreen);
    WindowSettings.Content[1] = std::to_string(WindowWidth);
    WindowSettings.Content[2] = std::to_string(WindowHeight);
    WindowSettings.Save("Window");
    Log.MESSAGE("Window Size Saved");
}