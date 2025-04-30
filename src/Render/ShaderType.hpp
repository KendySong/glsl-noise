#pragma once
#include <string>

enum class ShaderType : std::uint32_t
{
    Gradient   = 0,
    Turbulence = 1,
    TurbulenceRidget = 2,
    Cellular = 3,
    Value = 4,
    Count = 5
};

std::string getString(ShaderType type);