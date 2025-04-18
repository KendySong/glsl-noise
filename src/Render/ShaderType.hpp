#pragma once
#include <string>

enum class ShaderType : std::uint32_t
{
    Gradient   = 0,
    Turbulence = 1,
    TurbulenceRidget = 2,
    Value = 3,
    Count = 4
};

std::string getString(ShaderType type);