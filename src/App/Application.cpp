#include <glad/glad.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Application.hpp"
#include "../Settings.hpp"
#include "Sandbox.hpp"

Application* Application::s_app = nullptr;

Application* Application::instance()
{
    if (s_app == nullptr)
    {
        s_app = new Application();
    }
    return s_app;
}

Application::Application()
{
    //Create window
    glfwInit();
    p_window = glfwCreateWindow(Settings::width, Settings::height, "glsl noise", NULL, NULL);
    glfwWindowHint(GL_MINOR_VERSION, 4);
    glfwWindowHint(GL_MAJOR_VERSION, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwMakeContextCurrent(p_window);

    //Load and init OpenGL
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, Settings::width, Settings::height);
    glClearColor(0, 0, 0, 1);

    //Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(p_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    
    //Set callbacks
    glfwSetKeyCallback(p_window, key_callback);
}

int Application::run()
{
    Sandbox sandbox;
    while (!glfwWindowShouldClose(p_window))
    {
        glfwPollEvents();

        //Update
        sandbox.update();

        //Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        sandbox.render();
        sandbox.handleGui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());      
        glfwSwapBuffers(p_window);
    }

    glfwTerminate();
    return 0;
}
 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        }
    }
}