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
    m_size = glm::vec2(16, 9);
    m_octaves = 2;
    m_amplitude = 1.0;
    m_frequency = 1.0;
    m_persistence = 0.5;
    m_lacunarity = 2.0;

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

    m_main.setInt("uOctaves", m_octaves);
    m_main.setVec2("uSize", m_size);
    m_main.setFloat("uAmplitude", m_amplitude);
    m_main.setFloat("uFrequency", m_frequency);
    m_main.setFloat("uLacunarity", m_lacunarity);
    m_main.setFloat("uPersistence", m_persistence);
}

void Sandbox::handleGui()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::BeginMainMenuBar();
        ImGui::Text("FPS : %i", m_fps);
    ImGui::EndMainMenuBar();

    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Shader");
        ImGui::SetNextItemWidth(200);
        ImGui::DragFloat2("Map Size", &m_size.x, 0.5);
        ImGui::SetNextItemWidth(200);
        ImGui::DragInt("Octaves", &m_octaves, 1.0, 1);
        ImGui::SetNextItemWidth(200);
        ImGui::DragFloat("Amplitude", &m_amplitude, 0.05);
        ImGui::SetNextItemWidth(200);
        ImGui::DragFloat("Frequency", &m_frequency, 0.05);
        ImGui::SetNextItemWidth(200);
        ImGui::DragFloat("Lacunarity", &m_lacunarity, 0.05);
        ImGui::SetNextItemWidth(200);
        ImGui::DragFloat("Persistence", &m_persistence, 0.05);
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