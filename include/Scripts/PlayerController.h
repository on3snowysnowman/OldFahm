#pragma once

#include "Script.h"
#include "HarvestPlant.h"
#include "../Entity.h"
#include "../InputHandler.h"
#include "../CollisionHandler.h"
#include "../Components/TransformComponent.h"


struct PlayerController : public Script
{
    InputHandler* input_handler;

    PlayerController(InputHandler* _input_handler)
    {
        input_handler = _input_handler;
    }

    Script* clone() override
    {
        return new PlayerController(input_handler);
    }

    static std::string name()
    {
        return "PlayerController";
    }

    /**
     * @brief Modifies the Entity this Component is attatched to's position
     * based on the passed parameters
     * 
     * @param x_delta Change to the x value
     * @param y_delta Change to the y value
     */
    void modify_position(TransformComponent* t_comp, 
        int x_delta, int y_delta)
    {
        // Get the Component's current position
        int x_pos = t_comp->x_pos;
        int y_pos = t_comp->y_pos;

        // If the traversable check for the entities at this position does not 
        // return true
        if(!CollisionHandler::is_traversable(entity, x_pos + x_delta, 
            y_pos + y_delta))
        {
            return;
        }

        // Update the TransformComponent's Position
        t_comp->y_pos = y_pos + y_delta;
        t_comp->x_pos = x_pos + x_delta;

        // Update the Entity's EntityHandler's position of where 
        // the Entity this Component is attatched to lies
        entity->entity_handler->remove_entity(
            entity, x_pos, y_pos);
        entity->entity_handler->add_entity(
            entity, x_pos + x_delta, y_pos + y_delta);
    }

    /**
     * @brief Iterates through the keys in the input handler and performs logic
     * upon this Component's entity
     */
    void update() override 
    {
        // Assume that this entity has a transform component, as 
        // all entities should
        TransformComponent* t_comp = entity->get_component
            <TransformComponent>();

        for(Key* k : input_handler->get_active_keys())
        {
            switch(k->id)
            {
                case SDLK_w:

                    modify_position(t_comp, 0, -1);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_e:

                    modify_position(t_comp, 1, -1);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_d:

                    modify_position(t_comp, 1, 0);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_c:

                    modify_position(t_comp, 1, 1);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_s:

                    modify_position(t_comp, 0, 1);
                    input_handler->set_delay(k->id);
                    break;
                
                case SDLK_x:

                    modify_position(t_comp, 0, 1);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_z:

                    modify_position(t_comp, -1, 1);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_a:

                    modify_position(t_comp, -1, 0);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_q:

                    modify_position(t_comp, -1, -1);
                    input_handler->set_delay(k->id);
                    break;

                case 't':

                    modify_position(t_comp, -(t_comp->x_pos - 1), 
                        -(t_comp->y_pos - 1));
                    input_handler->set_delay(k->id);
                    break;

                case 'h':

                    if(entity->has_script<HarvestPlant>())
                    {
                        HarvestPlant* h_script = entity->get_script<
                            HarvestPlant>();
                        if(h_script->harvest())
                        { 
                            input_handler->set_delay(k->id);
                        }
                    }

                    break;
            }
        }
    }
};
