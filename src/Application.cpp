#include <glad/glad.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Application.hpp"
#include "Settings.hpp"

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
    glfwInit();
    p_window = glfwCreateWindow(Settings::width, Settings::height, "glsl noise", NULL, NULL);
    glfwWindowHint(GL_MINOR_VERSION, 4);
    glfwWindowHint(GL_MAJOR_VERSION, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwMakeContextCurrent(p_window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, Settings::width, Settings::height);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(p_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

int Application::run()
{
    while (!glfwWindowShouldClose(p_window))
    {
        glfwPollEvents();

        //Update


        //Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport();
        ImGui::Begin("Shader");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(p_window);
    }
    return 0;
}
  