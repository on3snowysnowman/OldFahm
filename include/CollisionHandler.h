#pragma once

#include <list>

#include "Entity.h"
#include "Components/ColliderComponent.h"
#include "Debug.h"

struct CollisionHandler
{
    static bool is_traversable_without_collider(Entity* e, int x, int y)
    {
        std::list<Entity*> entities =
            e->entity_handler->get_entities_at_position(x, y);

        for(std::list<Entity*>::iterator it = entities.begin();
            it != entities.end(); it++)
        {
            for(std::string tag : (*it)->tags)
            {
                if(tag == "NON_TRAVERSABLE")
                {   
                    return false;
                }
            }   
        }

        return true;
    }

    static bool is_traversable_with_collider(Entity* e, int x, int y)
    {
        std::list<Entity*> entities =
            e->entity_handler->get_entities_at_position(x, y);

        for(std::list<Entity*>::iterator it = entities.begin(); 
            it != entities.end(); it++)
        {
            if((*it)->has_component<ColliderComponent>())
            {

                if(!(*it)->get_component<ColliderComponent>()->collide(e->tags))
                {
                    return false;
                }
            }
        }

        return true;
    }

    static std::vector<std::pair<int,int>> 
        get_available_surrounding_positions(Entity* e, int x, int y)
    {
        std::vector<std::pair<int,int>> available_positions;

        for(int y_it = y - 1; y_it <= y + 1; y_it++)
        {
            for(int x_it = x - 1; x_it <= x + 1; x_it++)
            {
                if(y_it != y || x_it != x)
                {
                    // Entity has a collider attatched to it

                    if(e->has_component<ColliderComponent>())
                    {
                        if(is_traversable_with_collider(e, x_it, y_it))
                        {
                            available_positions.push_back({x_it, y_it});
                        }

                        continue;
                    }

                    // Entity does not have a collider

                    if(is_traversable_without_collider(e, x_it, y_it))
                    {
                        available_positions.push_back({x_it, y_it});
                    }

                }
            }
        }

        return available_positions;
    }

};
