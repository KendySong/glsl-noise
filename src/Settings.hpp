#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <ImGui/imgui.h>

class Settings
{
public :
    static const std::uint32_t width;
    static const std::uint32_t height;
    static const ImVec2 fbSize;
};