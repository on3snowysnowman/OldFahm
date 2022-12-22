#pragma once

#include "Script.h"
#include "../Entity.h"
#include "../InputHandler.h"
#include "../CollisionHandler.h"
#include "../Windows/TilemapWindow.h"

struct CursorController : public Script
{ 
    InputHandler* input_handler;
    TilemapWindow* tilemap_window;

    CursorController(InputHandler* _input_handler, 
        TilemapWindow* _tilemap_window)
    {
        input_handler = _input_handler;
        tilemap_window = _tilemap_window;
    }

    Script* clone() override
    {
        return new CursorController(input_handler, tilemap_window);
    }

    static std::string name()
    {
        return "CursorController";
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
        // if(!CollisionHandler::is_traversable_without_collider(entity, x_pos + x_delta, 
        //     y_pos + y_delta))
        // {
        //     return;
        // }

        if(!tilemap_window->is_position_within_render_bounds(x_pos + x_delta, 
            y_pos + y_delta) || !CollisionHandler::
            is_traversable_without_collider(entity, x_pos + x_delta,
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

        std::vector<Key*> active_keys =    
            input_handler->get_active_keys();
        
        if(active_keys.size() == 0) return;

        int first_key_id = active_keys.at(0)->id;

        switch(first_key_id)
        {
            case SDLK_w:

                modify_position(t_comp, 0, -1);
                input_handler->set_delay(first_key_id);
                break;

            case SDLK_e:

                modify_position(t_comp, 1, -1);
                input_handler->set_delay(first_key_id);
                break;

            case SDLK_d:

                modify_position(t_comp, 1, 0);
                input_handler->set_delay(first_key_id);
                break;

            case SDLK_c:

                modify_position(t_comp, 1, 1);
                input_handler->set_delay(first_key_id);
                break;

            case SDLK_s:

                modify_position(t_comp, 0, 1);
                input_handler->set_delay(first_key_id);
                break;
            
            case SDLK_x:

                modify_position(t_comp, 0, 1);
                input_handler->set_delay(first_key_id);
                break;

            case SDLK_z:

                modify_position(t_comp, -1, 1);
                input_handler->set_delay(first_key_id);
                break;

            case SDLK_a:

                modify_position(t_comp, -1, 0);
                input_handler->set_delay(first_key_id);
                break;

            case SDLK_q:

                modify_position(t_comp, -1, -1);
                input_handler->set_delay(first_key_id);
                break;
        }
    }

};
