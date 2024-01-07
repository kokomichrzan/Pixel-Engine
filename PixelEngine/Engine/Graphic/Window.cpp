#include "pch.h"
#include "Window.h"

namespace PE {

    Window::Window()
    {
        Settings WindowSettings = Settings();
        Data::Array SettingsData = Data::Array("Settings", 4);
        SettingsData.Read("Window");
        if (!SettingsData.Exist("Window")) {
            SettingsData.Content[0] = std::to_string(WindowSettings.FullScreen);
            SettingsData.Content[1] = std::to_string(WindowSettings.Width);
            SettingsData.Content[2] = std::to_string(WindowSettings.Height);
            SettingsData.Content[3] = std::to_string(WindowSettings.RefreshRate);

            SettingsData.Save("Window");
            LOG::MESSAGE("Create Window Settings");

        }
        else {
            WindowSettings.FullScreen = std::stoi(SettingsData.Content[0]);
            WindowSettings.Width = std::stoi(SettingsData.Content[1]);
            WindowSettings.Height = std::stoi(SettingsData.Content[2]);
            WindowSettings.RefreshRate = std::stoi(SettingsData.Content[3]);

            LOG::MESSAGE("Loaded Window Settings");
        }

        glfwInit();

        FullScreen = WindowSettings.FullScreen;
        RefreshRate = WindowSettings.RefreshRate;

        GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);

        if (WindowSettings.RefreshRate == 0) {
            glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate);
            LOG::MESSAGE("Setted Refresh Rate to " + std::to_string(Mode->refreshRate));
        }
        else {
            glfwWindowHint(GLFW_REFRESH_RATE, WindowSettings.RefreshRate);
            LOG::MESSAGE("Setted Refresh Rate to " + std::to_string(WindowSettings.RefreshRate));
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (WindowSettings.FullScreen) {
            WindowSettings.Width = Mode->width;
            WindowSettings.Height = Mode->height;
        }
        if (WindowSettings.Width < 1000) WindowSettings.Width = 1000;
        if (WindowSettings.Height < 900) WindowSettings.Height = 900;
        LOG::MESSAGE("Seted Resolution on " + std::to_string(WindowSettings.Width) + " x " + std::to_string(WindowSettings.Height));

        if (WindowSettings.FullScreen)
        {
            HWindow = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), Monitor, NULL);
            LOG::MESSAGE("Create Full Screen Window");
        }
        else
        {
            HWindow = glfwCreateWindow(WindowSettings.Width, WindowSettings.Height, WindowTitle.c_str(), NULL, NULL);
            LOG::MESSAGE("Create Window");
        }
        if (!HWindow) LOG::WARNING("Can not Create Window");

        glfwSetWindowPos(HWindow, (Mode->width - WindowSettings.Width) / 2, (Mode->height - WindowSettings.Height) / 2); //Set Window Position
        glfwSetWindowSizeLimits(HWindow, 1000, 900, GLFW_DONT_CARE, GLFW_DONT_CARE); //Set Window MinSize
        glfwMakeContextCurrent(HWindow);

        gladLoadGL();
        glad_glViewport(0, 0, WindowSettings.Width, WindowSettings.Height);
        LOG::MESSAGE("Loaded GLAD");

        LOG::INFO("Window Created");
    }

    Window::~Window() {
        SaveWindowParams();
        glfwDestroyWindow(HWindow);
        glfwTerminate();
    }

    void Window::Events() {
        ToggleFullscreen();
    }

    void Window::ToggleFullscreen() {
        if (glfwGetKey(HWindow, GLFW_KEY_F11) == GLFW_PRESS) {
            if (!F11Pressed) {
                F11Pressed = true;
                FullScreen = !FullScreen;
                GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);
                if (FullScreen) {
                    glfwSetWindowMonitor(HWindow, Monitor, 0, 0, Mode->width, Mode->height, RefreshRate);
                }
                else {
                    WindowWidth = 1000;
                    WindowHeight = 900;
                    glfwSetWindowMonitor(HWindow, NULL, (Mode->width - WindowWidth) / 2, (Mode->height - WindowHeight) / 2, WindowWidth, WindowHeight, RefreshRate);
                }
            }
        }
        else F11Pressed = false;
    }

    void Window::SaveWindowParams() {
        glfwGetWindowSize(HWindow, &WindowWidth, &WindowHeight);
        Data::Array WindowSettings = Data::Array("Settings", 4);
        WindowSettings.Read("Window");
        WindowSettings.Content[0] = std::to_string(FullScreen);
        WindowSettings.Content[1] = std::to_string(WindowWidth);
        WindowSettings.Content[2] = std::to_string(WindowHeight);
        WindowSettings.Save("Window");
        LOG::MESSAGE("Window Size Saved");
    }
}