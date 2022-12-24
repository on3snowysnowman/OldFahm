#pragma once

#include <vector>

#include "Component.h"
#include "SpriteComponent.h"
#include "../Entity.h"
#include "Text.h"

struct StorageComponent : public Component
{
    std::vector<Entity*> stored_entities;

    int max_entities;

    StorageComponent()
    {
        max_entities = -1;
    }

    StorageComponent(int _max_entities)
    {
        max_entities = _max_entities;
    }

    static std::string name()
    {
        return "StorageComponent";
    }

    void add_entity(Entity* e)
    {
        if(max_entities != -1 && stored_entities.size() >= max_entities)
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

    std::vector<std::pair<Text, int>> get_storage_display()
    {
        std::vector<std::pair<Text, int>> display;

        std::map<std::string, std::pair<int, std::string>> num_entities;

        for(Entity* e : stored_entities)
        {
            if(num_entities.count(e->name) != 0)
            {
                num_entities[e->name].first++;
                continue;
            }

            SpriteComponent* targ_e_s_comp = e->get_component<
                SpriteComponent>();

            num_entities.emplace(e->name, std::pair<int, std::string>{1, 
                targ_e_s_comp->color});
        }

        for(std::map<std::string, std::pair<int, std::string>>::iterator it = num_entities.begin();
            it != num_entities.end(); it++)
        {
            display.push_back(std::pair<Text, int>(Text(it->first,
                it->second.second), it->second.first));
        }

        return display;
    }

};
