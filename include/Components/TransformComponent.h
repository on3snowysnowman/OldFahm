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
        name = "TransformComponent";
    }

    TransformComponent(int x, int y)
    {
        x_pos = x;
        y_pos = y;
        name = "TransformComponent";
    }

    Component* clone() override
    {
        return new TransformComponent(x_pos, y_pos);
    }

    ~TransformComponent() {}

    void set_position(int x, int y)
    {
        x_pos = x;
        y_pos = y;
    }
};
