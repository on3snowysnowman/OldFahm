#pragma once 

#include <unordered_set>

#include "../Entity.h"

struct ColliderComponent: public Component
{
    /**
     * @brief Vector of 'tag' instances, where
     *  if any entity contains a tag that is present in this vector, it 
     *  will be allowed to traverse over the entity with this component. For 
     *  instance, if this collider component were attached to a Magma Entity,
     *  one of the exceptions that would be placed inside this set would be 
     *  "CAN_TRAVERSE_MAGMA", for entities that can move over magma tiles. 
     */
    std::unordered_set<std::string> exceptions; 

    ColliderComponent() {}

    ColliderComponent(std::unordered_set<std::string> _exceptions) 
    {
        exceptions = _exceptions;
    }

    Component* clone() override
    {
        return new ColliderComponent(exceptions);
    }

    nlohmann::json serialize() override
    {
        nlohmann::json save_json;

        save_json["name"] = name();
        
        nlohmann::json exceptions_save_array = nlohmann::json::array();

        for(std::unordered_set<std::string>::iterator it = exceptions.begin();
            it != exceptions.end(); it++)
        {
            exceptions_save_array.push_back(*it);
        }

        save_json["exceptions"] = exceptions_save_array;

        
    }

    static std::string name()
    {
        return "ColliderComponent";
    }

    ~ColliderComponent() {}

    /**
     * @brief Called when an entity attempts to move over the same space 
     * where this component is present. Returns whether the entity 
     * attempting to move here is allowed to do so based on its tags
     * 
     * @param e Entity colliding with this component
     * @return true if the entity can move here
     */
    bool collide(std::vector<std::string> entity_tags)
    {
        // Iterate through the target entity's tags
        for(std::string targ_t : entity_tags)
        {
            // If this tag is present in the exceptions, allow it to
            // traverse over this tile
            if(exceptions.count(targ_t) > 0) return true;
        }
        return false;
    }
};