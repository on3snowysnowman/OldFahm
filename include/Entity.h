#pragma once

#include <list>
#include <string>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <vector>

#include "Scripts/Script.h"
#include "Components/Component.h"
#include "Components/SpriteComponent.h"
#include "Debug.h"

struct Entity;

struct EntityScriptTracker
{
    static std::vector<Entity*> entities;

    static void remove_entity(Entity* e)
    {
        for(int i = 0; i < entities.size(); i++)
        {
            if(entities.at(i) == e)
            {
                entities.erase(entities.begin() + i);
            }
        }
    }
};

class EntityHandler;

struct Entity
{
    std::string name;
    std::unordered_set<std::string> tags;

    std::vector<Component*> components;
    std::unordered_set<std::string> component_names;

    std::vector<Script*> scripts;
    std::unordered_set<std::string> script_names;
    
    EntityHandler* entity_handler = nullptr;

    Entity() {}

    Entity(std::string _name)
    {
        name = _name;
    }

    Entity(const Entity& e)
    {
        // Name

        name = e.name;

        // Tags

        for(std::string t : e.tags)
        {
            add_tag(t);
        }

        // Components

        for(Component* c : e.components)
        {
            Component* copy_c = c->clone();

            components.push_back(copy_c);
            component_names.emplace(copy_c->name);
        }

        // Scripts

        for(Script* s : e.scripts)
        {
            Script* copy_s = s->clone();

            scripts.push_back(copy_s);
            script_names.emplace(copy_s->name);
        }

    }

    ~Entity()
    {
        for(Component* c : components)
        {
            delete c;
        }
        
        for(Script* s : scripts)
        {
            delete s;
        }
    }

    bool has_script(std::string script_name)
    {
        return script_names.count(script_name);
    }

    bool has_component(std::string component_name)
    {
        return component_names.count(component_name);
    }

    void add_tag(std::string tag) 
    {
        tags.emplace(tag);
    }

    void remove_tag(std::string tag)
    {
        tags.erase(tag);
    }

    void add_script(Script* s)
    {

        if(script_names.count(s->name) == 1)
        {
            std::string message = "[WAR] Attempted to attach script: "
                + s->name + " to entity: " + name + ", when an identical"
                " script already exists";
            Debug::log(message);
            return;
        }

        scripts.push_back(s);
        script_names.emplace(s->name);

        s->entity = this;

        if(scripts.size() == 1) 
        {
            EntityScriptTracker::entities.push_back(this);
        }
    }

    void add_component(Component* c)
    {
        if(component_names.count(c->name) == 1)
        {
            std::string message = "[WAR] Attempted to attach component: "
                + c->name + " to entity: " + name + ", when an identical"
                " component already exists";
            Debug::log(message);
            return;
        }

        components.push_back(c);
        component_names.emplace(c->name);
    }

    Script* get_script(std::string script_name) 
    {
        if(script_names.count(script_name) == 0)
        {
            std::string message = "[WAR] Entity.get_script -> Attempted to get"
                " script: " + script_name + " from entity: " + name + 
                ", when no matching script exists";
            Debug::log(message);
            return nullptr;
        }

        for(Script* s : scripts)
        {
            if(s->name == script_name)
            {
                return s;
            }
        }

        return nullptr;
    }

    Script* remove_script(std::string script_name)
    {

        if(script_names.count(script_name) == 0)
        {
            std::string message = "[WAR] Attempted to delete script: " 
            + script_name + " from entity: " + name + ", but no script"
            " with that name was found";

            Debug::log(message);
            return nullptr;
        }

        script_names.erase(script_name);
        
        for(int i = 0; i < scripts.size(); i++)
        {
            if(scripts.at(i)->name == script_name)
            {
                Script* targ_script = scripts.at(i);

                scripts.erase(scripts.begin() + i);

                if(scripts.size() == 0)
                {
                    EntityScriptTracker::remove_entity(this);
                }

                return targ_script;
            }
        }
    
        return nullptr;
    }

    Component* get_component(std::string component_name) 
    {
        if(component_names.count(component_name) == 0)
        {
            std::string message = "[WAR] Entity.get_component -> Attempted to get"
                " component: " + component_name + " from entity: " + name + 
                ", when no matching component exists";
            Debug::log(message);
            return nullptr;
        }

        for(Component* c : components)
        {
            if(c->name == component_name)
            {
                return c;
            }
        }

        return nullptr;
    }

    Component* remove_component(std::string component_name)
    {

        if(component_names.count(component_name) == 0)
        {
            std::string message = "[WAR] Attempted to delete script: " 
            + component_name + " from entity: " + name + ", but no script"
            " with that name was found";

            Debug::log(message);
            return nullptr;
        }

        script_names.erase(component_name);
        
        for(int i = 0; i < components.size(); i++)
        {
            if(components.at(i)->name == component_name)
            {
                components.erase(components.begin() + i);

                return components.at(i);
            }
        }

        return nullptr;
    }

};

struct compare_entity_priority
{
    bool operator() (Entity* e_1, Entity* e_2)
    {
        SpriteComponent* s_component_1 = 
            static_cast<SpriteComponent*>(e_1->get_component(
                "SpriteComponent"));
            
        SpriteComponent* s_component_2 = 
            static_cast<SpriteComponent*>(e_2->get_component(
                "SpriteComponent"));

        return s_component_1->priority > s_component_2->priority;
    }
};

class EntityHandler
{

private:

    std::map<std::pair<int,int>, std::list<Entity*>> entity_positions;

    int width;
    int height;

public:

    EntityHandler() {}

    EntityHandler(int _width, int _height)
    {
        width = _width;
        height = _height;
    }

    ~EntityHandler() {}

    void delete_all_entities()
    {
        for(std::map<std::pair<int,int>, std::list<Entity*>>
            ::iterator it = entity_positions.begin(); 
            it != entity_positions.end(); it++)
        {
            for(Entity* e : it->second) delete e;
        }
    }

    void update()
    {
        for(Entity* e : EntityScriptTracker::entities)
        {
            for(Script* s : e->scripts)
            {
                s->update();
            }
        }
    }

    void add_entity(Entity* e, int x, int y)
    {
        e->entity_handler = this;
        entity_positions[{x, y}].push_back(e);
        sort_entities_at_position(x, y);
    }

    void sort_entities_at_position(int x, int y)
    {
        entity_positions[{x, y}].sort(compare_entity_priority());
    }

    bool remove_entity(Entity* e, int x, int y)
    {
        for(int i = 0; i < entity_positions[{x, y}].size(); i++)
        {

            for(std::list<Entity*>::iterator it = entity_positions
                [{x, y}].begin(); it != entity_positions[{x, y}].end(); 
                it++)
            {
                if(*it == e)
                {
                    entity_positions[{x, y}].erase(it);
                        return true;
                }
            }

            // if(entity_positions[{x, y}].at(i) == e)
            // {
            //     entity_positions[{x, y}].erase(
            //         entity_positions[{x, y}].begin() + i);
            //     return true;
            // }
        }
        return false;
    }

    std::list<Entity*> get_entities_at_position(int x, int y)
    {
        if(entity_positions.count({x, y}) == 0)
        {
            std::list<Entity*> temp;
            return temp;
        }

        return entity_positions[{x, y}];
    }

    std::map<std::pair<int,int>, std::list<Entity*>> get_all_entities()
    {
        return entity_positions;
    }

};

