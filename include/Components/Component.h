#pragma once

struct Entity;

struct Component
{
    Entity* entity = nullptr;
    std::string name;

    Component() {}

    virtual Component* clone() { return new Component(); }

    ~Component() {}
};
