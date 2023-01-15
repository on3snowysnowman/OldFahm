#pragma once

#include <nlohmann/json.hpp>

struct Entity;

struct Component
{
    Entity* entity = nullptr;

    Component() {}

    virtual Component* clone() { return new Component(); }
    virtual nlohmann::json serialize() {}

    static std::string name() { return "Component"; }

    ~Component() {}
};
