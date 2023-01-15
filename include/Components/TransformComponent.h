#pragma once

#include "Component.h"

struct TransformComponent : public Component
{
    int x_pos;
    int y_pos;

    TransformComponent()
    {
        x_pos = 0;
        y_pos = 0;
    }

    TransformComponent(int x, int y)
    {
        x_pos = x;
        y_pos = y;
    }

    Component* clone() override
    {
        return new TransformComponent(x_pos, y_pos);
    }

    nlohmann::json serialize() override
    {
        nlohmann::json save_json;

        save_json["name"] = name();
        save_json["x_pos"] = x_pos;
        save_json["y_pos"] = y_pos;

        return save_json;
    }

    static std::string name()
    {
        return "TransformComponent";
    }

    ~TransformComponent() {}

    void set_position(int x, int y)
    {
        x_pos = x;
        y_pos = y;
    }
};
