#pragma once
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "Graphic/Window.h"
#include "Graphic/Gui.h"
#include <future>

namespace PE {

    class Application
    {
    private:
        PE::Window *Window;

    public:
        Application();

    };

}