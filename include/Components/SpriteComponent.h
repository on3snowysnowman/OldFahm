#pragma once

#include <string>

#include "Component.h"
#include "TileID.h"

struct SpriteComponent : public Component
{
    TileID tile_id;
    int priority;
    
    SpriteComponent()
    {
        tile_id = NO_ID;
        priority = -1;
    }

    SpriteComponent(TileID _tile_id, int _priority) 
    {
        tile_id = _tile_id;
        priority = _priority;
    }

    Component* clone() override
    {
        return new SpriteComponent(tile_id, priority);
    }

    nlohmann::json serialize() override
    {
        nlohmann::json save_json;

        save_json["name"] = name();
        save_json["tile_id"] = tile_id;
        save_json["priority"] = priority;

        return save_json;

    }

    static std::string name()
    {
        return "SpriteComponent";
    }
};
