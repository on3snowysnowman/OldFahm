#pragma once

#include <string>

#include "Component.h"

struct SpriteComponent : public Component
{
    char symbol;
    std::string color;
    int priority;
    
    SpriteComponent()
    {
        symbol = ' ';
        color = "WHITE";
        priority = 0;
    }

    SpriteComponent(char _symbol, std::string _color, int _priority) 
    {
        symbol = _symbol;
        color = _color;
        priority = _priority;
    }

    Component* clone() override
    {
        return new SpriteComponent(symbol, color, priority);
    }

    static std::string name()
    {
        return "SpriteComponent";
    }
};
