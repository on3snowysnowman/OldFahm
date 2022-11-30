#pragma once

#include <string>
#include <iostream>

struct Entity;

/**
 * @brief Modular class for attaching behavior to entities
 */
struct Script
{

    std::string name;
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
