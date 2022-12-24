#pragma once

#include "Script.h"
#include "../Text.h"
#include "../Components/StorageComponent.h"
#include "../Components/SpriteComponent.h"

struct DisplayStorage : public Script
{

    std::vector<Text>* text_to_output;
    StorageComponent* s_comp;

    DisplayStorage()
    {
        s_comp = nullptr;
        Debug::log("[WARN] DisplayInventory.DefaultConstructor -> "
            "Default Constructor used, initialized null pointers");
    }

    DisplayStorage(std::vector<Text>* _target_text_output, 
        StorageComponent* _storage_component)
    {
        text_to_output = _target_text_output;
        s_comp = _storage_component;
    }

    Script* clone() override
    {
        return new DisplayStorage(text_to_output, s_comp);
    }

    void update() override
    {
        for(Entity* e : s_comp->stored_entities)
        {
            SpriteComponent* sprite_comp = 
                e->get_component<SpriteComponent>();

            text_to_output->push_back(Text(e->name, "WHITE"));
        }
    }

};
