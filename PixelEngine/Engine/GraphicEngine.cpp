#include "GraphicEngine.h"

GLFWwindow* GraphicEngine::CreateWindow()
{
    //Load Settings
    Settings WindowSettings = Settings();
    Data::Array SettingsData = Data::Array("Settings", 4);
    SettingsData.Read("Window");
    if(!SettingsData.Exist("Window")){
        SettingsData.Content[0] = std::to_string(WindowSettings.FullScreen);
        SettingsData.Content[1] = std::to_string(WindowSettings.Width);
        SettingsData.Content[2] = std::to_string(WindowSettings.Height);
        SettingsData.Content[3] = std::to_string(WindowSettings.RefreshRate);

        SettingsData.Save("Window");
        Log.INFO("Create Window Settings");

    }else{
        WindowSettings.FullScreen =     std::stoi(SettingsData.Content[0]);
        WindowSettings.Width =          std::stoi(SettingsData.Content[1]);
        WindowSettings.Height =         std::stoi(SettingsData.Content[2]);
        WindowSettings.RefreshRate =    std::stoi(SettingsData.Content[3]);

        Log.INFO("Loaded Window Settings");
    }

    //Init Window
    glfwInit();

    //Set Fullscreen and Refresh Rate
    FullScreen = WindowSettings.FullScreen;
    RefreshRate = WindowSettings.RefreshRate;

    //Get Window Params
    GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);

    //Refresh Rate
    if(WindowSettings.RefreshRate == 0) {glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate); 
    Log.INFO("Setted Refresh Rate to " + std::to_string(Mode->refreshRate));}
    else{ glfwWindowHint(GLFW_REFRESH_RATE, WindowSettings.RefreshRate); 
    Log.INFO("Setted Refresh Rate to " + std::to_string(WindowSettings.RefreshRate));}
    
    //Set Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Remove TopBar
    glfwWindowHint(GLFW_DECORATED, false);

    //Set Resolution
    if(WindowSettings.FullScreen){
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
    if(!Window) Log.WARNING("Can not Create Window");
    
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
    //Get Data
    glfwGetCursorPos(Window, &MouseX, &MouseY);
    glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);
    glfwGetWindowPos(Window, &WindowLastX, &WindowLastY);

    //Check if User is pressing key inside window
    if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && //Is Left Button Pressed
    (( MouseX >= EventResizeSize && MouseX <= WindowWidth - EventResizeSize && 
    MouseY >= EventResizeSize && MouseY <= WindowHeight - EventResizeSize) || (MouseInSideLock)) && //Cursor is inside window
    !(ResizeTopLock || ResizeBottomLock || ResizeLeftLock || ResizeRightLock)) //Is not currently Resize
    MouseInSideLock = true;
    else MouseInSideLock = false;

    //Check if you can resize window
    if(!MoveEvent && !MouseInSideLock && !FullScreen)
    {
        //Left Resize
        if(((MouseX < EventResizeSize && //Check if cursor is on left border
        MouseY > 30 && (MouseY < (WindowHeight - EventResizeSize))) || ResizeLeftLock) && //Check if is not on topbar and bottombar adn if is lock
        !(ResizeTopLock || ResizeBottomLock || ResizeRightLock)) { //Check if is not currently resize else edge
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                //Get First Data
                if(ResizeGetEvent) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    ResizeGetEvent = false;
                    //Set Reszie Left
                    ResizeLeftLock = true;
                    //Resize
                    if((WindowWidth - (MouseX - MouseLastX)) >= 1000) { // Check Min Width
                        glfwSetWindowPos(Window, int(WindowLastX + (MouseX - MouseLastX)), WindowLastY); //Set New Window Pos
                        glfwSetWindowSize(Window, int(WindowWidth - (MouseX - MouseLastX)), WindowHeight); //Set New Window Size
                        glfwSetCursorPos(Window, MouseLastX, MouseLastY); //Set Cursor on Last position

                    }

                } else {ResizeGetEvent = true; ResizeLeftLock = false;};

            }

        //Right Resize
        if(((MouseX > (WindowWidth - EventResizeSize) &&  //Check if cursor is on right border
        MouseY > 30 && (MouseY < (WindowHeight - EventResizeSize))) || ResizeRightLock) && //Check if is not on topbar and bottombar adn if is lock
        !(ResizeTopLock || ResizeBottomLock || ResizeLeftLock)){ //Check if is not currently resize else edge
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                //Get First Data
                if(ResizeGetEvent) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    ResizeGetEvent = false;
                    //Set Reszie Right
                    ResizeRightLock = true;
                    if(MouseX >= 1000) // Check Min Width
                    glfwSetWindowSize(Window, int(MouseX), WindowHeight); //Set new Window Size

                } else {ResizeGetEvent = true; ResizeRightLock = false;};

        }

        //Top Resize
        if(((MouseY < EventResizeSize || ResizeTopLock)) && //Check if Cursor is on top edge and if is lock on top resize
        !(ResizeBottomLock || ResizeLeftLock || ResizeRightLock)){ //Check if is not currently resize else edge
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                //Get First Data
                if(ResizeGetEvent) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    ResizeGetEvent = false;
                    //Set Resize Top
                    ResizeTopLock = true;
                    if((WindowHeight - (MouseY - MouseLastY)) >= 900) { //Check Min Height
                        glfwSetWindowPos(Window, WindowLastX, int(WindowLastY + (MouseY - MouseLastY))); //Set New Window Pos
                        glfwSetWindowSize(Window, WindowWidth, int(WindowHeight - (MouseY - MouseLastY))); //Set New Window Size
                        glfwSetCursorPos(Window, MouseLastX, MouseLastY); //Set Cursor on Last position

                    }
                } else {ResizeGetEvent = true; ResizeTopLock = false;};

        }

        //Bottom Resize
        if((MouseY > (WindowHeight - EventResizeSize) || ResizeBottomLock) && //Check if Cursor is on bottom edge and if is lock on bottom resize
        !(ResizeTopLock || ResizeLeftLock || ResizeRightLock)){ //Check if is not currently resize else edge
            if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                //Get First Data
                if(ResizeGetEvent) {glfwGetCursorPos(Window, &MouseLastX, &MouseLastY); }
                    ResizeGetEvent = false;
                    //Set Resize Bottom
                    ResizeBottomLock = true;
                    if(MouseY >= 900) //Check Min Height
                    glfwSetWindowSize(Window, WindowWidth, int(MouseY)); //Set New Window Size

                } else {ResizeGetEvent = true; ResizeBottomLock = false;};
                
        }
        
        //Check Min Sizes
        if(WindowWidth < 1000) glfwSetWindowSize(Window, 1000, WindowHeight);
        if(WindowHeight < 900) glfwSetWindowSize(Window, WindowWidth, 900);
        //Set New GLad
        glViewport(0,0, WindowWidth, WindowHeight);

    }

}

void GraphicEngine::ToggleFullscreen(GLFWwindow* Window){
    //Check if F11 Pressed
    if(glfwGetKey(Window, GLFW_KEY_F11) == GLFW_PRESS){
        if(!F11Pressed){ //OneClick
            F11Pressed = true;
            //Togle Fullscreen
            FullScreen = !FullScreen;
            //Get Monitor Params
            GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);
            if(FullScreen){// Set Fullscreen Window
                glfwSetWindowMonitor(Window, Monitor, 0, 0, Mode->width, Mode->height, RefreshRate); 

            }else{ //Set Not Fullscreen Window
                //Set Window Size
                WindowWidth = 1000;
                WindowHeight = 900;
                glfwSetWindowMonitor(Window, NULL, (Mode->width - WindowWidth)/2, (Mode->height - WindowHeight)/2, WindowWidth, WindowHeight, RefreshRate); 
            
            }

        }
    }else F11Pressed = false;

}

void GraphicEngine::SaveWindowParams(GLFWwindow* Window){
    //Get Window Sizes
    glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);
    //Open Settings File
    Data::Array WindowSettings = Data::Array("Settings", 4);
    WindowSettings.Read("Window");
    //Set New Window Size
    WindowSettings.Content[0] = std::to_string(FullScreen);
    WindowSettings.Content[1] = std::to_string(WindowWidth);
    WindowSettings.Content[2] = std::to_string(WindowHeight);
    //Save File
    WindowSettings.Save("Window");
    Log.MESSAGE("Window Size Saved");

}