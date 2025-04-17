#pragma once
#include <string>

enum class ShaderType : std::uint32_t
{
    Gradient   = 0,
    Turbulence = 1,
    Count = 2
};

std::string getString(ShaderType type);