#pragma once

#include <vector>

#include "Component.h"
#include "../Entity.h"

struct StorageComponent : public Component
{

    std::vector<Entity*> stored_entities;

    int max_entities;

    StorageComponent()
    {
        max_entities = 0;
    }

    StorageComponent(int _max_entities)
    {
        max_entities = _max_entities;
    }

    void add_entity(Entity* e)
    {
        if(stored_entities.size() >= max_entities)
        {
            return;
        }

        stored_entities.push_back(e);
    }

    bool remove_entity(Entity* targ_e)
    {
        for(int i = 0; i < stored_entities.size(); i++)
        {
            if(stored_entities.at(i) == targ_e)
            {
                stored_entities.erase(stored_entities.begin() + i);
                return true;
            }
        }

        return false;
    }

};
