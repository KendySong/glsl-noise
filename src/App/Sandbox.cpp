#include <glad/glad.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Sandbox.hpp"
#include "../Settings.hpp"

Sandbox::Sandbox()
{
    m_fps = 0;
    m_fpsCounter = 0;   

    //Instance default shader and configure it
    m_main = Shader("../shaders/vert.glsl", "../shaders/frag.glsl");
    glUseProgram(m_main.id);
    glm::vec2 resolution(Settings::fbSize.x, Settings::fbSize.y);
    m_main.setVec2("uResolution", resolution);

    
    //Create framebuffer
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glGenTextures(1, &m_fbto);
    glBindTexture(GL_TEXTURE_2D, m_fbto);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Settings::width, Settings::height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fbto, 0);

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Settings::width, Settings::height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    
    m_planeShader = Rectangle(glm::vec3(0, 0, 0), glm::vec2(2, 2));
}

void Sandbox::update()
{
    this->countFPS();
    float dt = m_delta.getDeltaTime();
    m_main.setFloat("uTime", m_elapsed.getElapsedTime());
    m_main.setVec3("uPos", m_planeShader.position);

}

void Sandbox::handleGui()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::BeginMainMenuBar();
        ImGui::Text("FPS : %i", m_fps);
    ImGui::EndMainMenuBar();

    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Shader");
        //ImGui::SetNextItemWidth(150);
    ImGui::End();

    ImGui::Begin("Render");
        ImVec2 cursorPos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)m_fbo,
            cursorPos,
            ImVec2(cursorPos.x + Settings::fbSize.x, cursorPos.y + Settings::fbSize.y)
        );
    ImGui::End();
}

void Sandbox::draw()
{  
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_planeShader.draw();
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