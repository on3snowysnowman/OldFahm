#include "EntitySerializer.h"

nlohmann::json EntitySerializer::serialize_entity(Entity* e)
{
    nlohmann::json entity_save;


    // Name

    entity_save["name"] = e->name;


    // Tags

    nlohmann::json tags = nlohmann::json::array();

    for(std::string _tag : e->tags)
    {
        tags.push_back(_tag);
    }

    entity_save["tags"] = tags;


    // Components

    nlohmann::json components = nlohmann::json::array();

    for(std::pair<std::string, Component*> _pair : e->components)
    {
        components.push_back(_pair.second->serialize());
    }

    entity_save["components"] = components;


    // Scripts

    nlohmann::json scripts = nlohmann::json::array();

    for(Script* s : e->scripts)
    {
        scripts.push_back(s->serialize());
    }

    entity_save["scripts"] = scripts;

    return entity_save;
}
