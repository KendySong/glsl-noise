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
    }
    return "Default";
}