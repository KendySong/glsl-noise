#pragma once
#include <GLFW/glfw3.h>

class Application
{
public :
    static Application* instance();
    int run();

private :
    Application();
    static Application* s_app;
    GLFWwindow* p_window;
};