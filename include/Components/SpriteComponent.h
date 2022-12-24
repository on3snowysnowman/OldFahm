#pragma once

#include <string>

#include "Component.h"
#include "TileID.h"

struct SpriteComponent : public Component
{
    TileID symbol;
    int priority;
    
    SpriteComponent()
    {
        symbol = NO_ID;
        priority = -1;
    }

    SpriteComponent(TileID _symbol, int _priority) 
    {
        symbol = _symbol;
        priority = _priority;
    }

    Component* clone() override
    {
        return new SpriteComponent(symbol, priority);
    }

    static std::string name()
    {
        return "SpriteComponent";
    }
};
