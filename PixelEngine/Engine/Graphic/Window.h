#pragma once
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include "Data/Data.h"
#include "../LOG.h"

namespace PE {

    class Window
    {
    private:
        struct Settings {
            unsigned int Width = 1000,
                Height = 900,
                RefreshRate = 60;
            bool FullScreen = false;
        };

    private:
        const std::string WindowTitle = "Pixel Engine";
        double MouseLastX, MouseLastY, MouseX, MouseY;
        int WindowLastX, WindowLastY, WindowWidth, WindowHeight,
            RefreshRate = 60;
        bool MoveGetEvent = true, ResizeGetEvent = true, MoveEvent = false, MouseInSideLock = false,
            ResizeLeftLock = false, ResizeRightLock = false, ResizeTopLock = false, ResizeBottomLock = false,
            FullScreen = false, F11Pressed = false;
        const int EventResizeSize = 10;
        const int EventMoveSize = 30;
        void Move();
        void Resize();
        void ToggleFullscreen();

    public:
        Window();
        ~Window();
        void Render();
        GLFWwindow* HWindow;
        void Events();
        void SaveWindowParams();

    };
}