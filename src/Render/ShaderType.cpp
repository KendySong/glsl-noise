#include "ShaderType.hpp"

std::string getString(ShaderType type)
{
    switch (type)
    {
    case ShaderType::Gradient :
        return "Gradient";   
        break;

    case ShaderType::Turbulence :
        return "Turbulence";    
        break;

    case ShaderType::TurbulenceRidget:
        return "Turbulence Ridget";
        break;

    case ShaderType::Value:
        return "Value";
        break;  
    }
    return "Default";
}