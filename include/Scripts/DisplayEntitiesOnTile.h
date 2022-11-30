#pragma once

#include <vector>
#include <iostream>

#include "Script.h"
#include "../Entity.h"
#include "../Text.h"
#include "../Debug.h"
#include "../Components/TransformComponent.h"

struct DisplayEntitiesOnTile : public Script
{

    std::vector<Text>* text_to_render;
    Entity* targ_entity;

    DisplayEntitiesOnTile()
    {
        Debug::log("[WARN] DisplayEntitiesOnTile.DefaultConstructor -> "
            "Default constructor used, instanciating null pointers");
            targ_entity = nullptr;
    }

    DisplayEntitiesOnTile(Entity* _targ_entity, std::vector<Text>* target_text_output)
    {
        name = "DisplayEntitiesOnTile";
        targ_entity = _targ_entity;
        text_to_render = target_text_output;
    }

    void update() override
    {
        TransformComponent* t_comp = targ_entity->get_component
            <TransformComponent>();

        for(Entity* e : targ_entity->entity_handler->
            get_entities_at_position(t_comp->x_pos, t_comp->y_pos))
        {
            if(e == targ_entity) continue;

            SpriteComponent* s_comp = e->get_component<
                SpriteComponent>();

            text_to_render->push_back(Text(e->name, s_comp->color));
        }
    }

};
