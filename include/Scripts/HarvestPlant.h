#pragma once

#include "Script.h"
#include "../Components/StorageComponent.h"
#include "../Components/TransformComponent.h"
#include "../Entity.h"

struct HarvestPlant : public Script
{

    StorageComponent* s_comp;

    HarvestPlant()
    {
        s_comp = nullptr;
    }

    HarvestPlant(StorageComponent* targ_storage_component)
    {
        s_comp = targ_storage_component;
    }

    Script* clone() override
    {
        return new HarvestPlant(s_comp);
    }

    static std::string name()
    {
        return "HarvestPlant";
    }

    bool harvest()
    {
        TransformComponent* t_comp = entity->get_component<
            TransformComponent>();

        for(Entity* e : 
            entity->entity_handler->get_entities_at_position(
                t_comp->x_pos, t_comp->y_pos))
        {
            std::string targ_tag = e->get_tag("HARVESTABLE");

            if(targ_tag.size() > 0)
            {
                entity->entity_handler->remove_entity(e, t_comp->x_pos, 
                    t_comp->y_pos);
                s_comp->add_entity(e);
                return true;
            }
        }

        return false;
    }

};

