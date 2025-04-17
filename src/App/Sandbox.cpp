#include <glad/glad.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include <iostream>

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

    m_pause = false;
    m_elapsedTime = 0;
    m_current = ShaderType::Gradient;

    //Instance default shader and configure it
    m_shaders["Gradient"] = Shader("../shaders/vertex.glsl", "../shaders/gradient.glsl");
    m_shaders["Turbulence"] = Shader("../shaders/vertex.glsl", "../shaders/turbulence.glsl");

    glUseProgram(m_shaders[getString(m_current)].id);
    m_resolution = glm::vec2(Settings::fbSize.x, Settings::fbSize.y);
    m_pos = glm::vec2(0);
    
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
    if (!m_pause)
    {
        m_elapsedTime = m_elapsed.getElapsedTime();
    }
    
    m_shaders[getString(m_current)].setVec2("uResolution", m_resolution);
    m_shaders[getString(m_current)].setFloat("uTime", m_elapsedTime);
    m_shaders[getString(m_current)].setVec2("uPos", m_pos);
    m_shaders[getString(m_current)].setInt("uOctaves", m_octaves);
    m_shaders[getString(m_current)].setVec2("uSize", m_size);
    m_shaders[getString(m_current)].setFloat("uAmplitude", m_amplitude);
    m_shaders[getString(m_current)].setFloat("uFrequency", m_frequency);
    m_shaders[getString(m_current)].setFloat("uLacunarity", m_lacunarity);
    m_shaders[getString(m_current)].setFloat("uPersistence", m_persistence);
}

void Sandbox::handleGui()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::BeginMainMenuBar();
        ImGui::Text("FPS : %i", m_fps);
    ImGui::EndMainMenuBar();

    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Shader");
        ImGui::PushItemWidth(200);
        if (ImGui::BeginCombo("Shader type", getString(m_current).c_str()))
        {
            for (size_t i = 0; i < static_cast<int>(ShaderType::Count); i++)
            {
                bool selected = static_cast<int>(m_current) == i;
                ShaderType shaderType = static_cast<ShaderType>(i);
                if (ImGui::Selectable(getString(shaderType).c_str(), selected))
                {
                    m_current = shaderType;     
                    glUseProgram(m_shaders[getString(m_current)].id);
                }

                if (selected)
                {                  
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        
        ImGui::DragFloat2("Map Size", &m_size.x, 0.05);
        ImGui::DragFloat2("Offset", &m_pos.x, 0.001);
        ImGui::DragFloat("Time", &m_elapsedTime, 0.01);
        ImGui::Checkbox("Pause", &m_pause); 
        ImGui::SeparatorText("Noise parameters");
        ImGui::SliderInt("Octaves", &m_octaves, 1.0, 8);
        ImGui::DragFloat("Amplitude", &m_amplitude, 0.001);     
        ImGui::DragFloat("Frequency", &m_frequency, 0.001);   
        ImGui::DragFloat("Lacunarity", &m_lacunarity, 0.001, 1);      
        ImGui::DragFloat("Persistence", &m_persistence, 0.001, 0, 1);
        ImGui::PopItemWidth();
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