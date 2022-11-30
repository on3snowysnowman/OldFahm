#pragma once

struct Entity;

struct Component
{
    Entity* entity = nullptr;

    Component() {}

    virtual Component* clone() { return new Component(); }

    static std::string name() { return "Component"; }

    ~Component() {}
};
