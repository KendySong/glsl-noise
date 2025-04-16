#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Sandbox.hpp"

Sandbox::Sandbox()
{
    m_fps = 0;
    m_fpsCounter = 0;


}

void Sandbox::update()
{
    this->countFPS();
    float dt = m_delta.getDeltaTime();
    
}

void Sandbox::handleGui()
{
    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Shader");
        ImGui::Text("FPS : %i", m_fps);
    ImGui::End();
}

void Sandbox::render()
{

}

void Sandbox::countFPS()
{
    m_fpsCounter++;
    if (m_fpsChrono.getElapsedTime() >= 1)
    {
        m_fps = m_fpsCounter;
        m_fpsCounter = 0;
        m_fpsChrono.restart();
    }
}