#pragma once

#include <string>
#include <iostream>

struct Entity;

/**
 * @brief Modular class for attaching behavior to entities
 */
struct Script
{

    Entity* entity = nullptr;

    Script() 
    {
        start();
    }

    virtual Script* clone() 
    { 
        Script* s_clone = new Script();
        return s_clone; 
    }

    virtual nlohmann::json serialize() {}

    static std::string name()
    {
        return "Script";
    }

    ~Script() {}

    /**
     * @brief Called when the object is created
     */
    virtual void start() {}

    /**
     * @brief Called once per frame
     */

    virtual void update() {}
};
