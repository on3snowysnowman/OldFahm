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

struct EntityTracker
{
    static std::vector<Entity*> entities;

    // static std::map<std::size_t, std::string> component_ids;

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

// template<typename T>
// std::size_t get_component_id()
// {
//     static std::size_t component_id = 0;
//     return component_id++;
// }

struct Entity
{
    std::string name;
    std::vector<std::string> tags;

    std::map<std::string, Component*> components;

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

        components = e.components;

        // for(Component* c : e.components)
        // {
        //     Component* copy_c = c->clone();

        //     components.push_back(copy_c);
        //     component_names.emplace(copy_c->name);
        // }

        // Scripts

        for(Script* s : e.scripts)
        {
            Script* copy_s = s->clone();

            scripts.push_back(copy_s);
            script_names.emplace(copy_s->name());
        }

    }

    ~Entity()
    {
        for(std::map<std::string, Component*>::
            iterator it = components.begin(); it != 
            components.end(); it++)
        {
            delete it->second;
        }
        
        for(Script* s : scripts)
        {
            delete s;
        }
    }

    template<typename T>
    bool has_script()
    {
        return script_names.count(T::name());
    }

    template<typename T>
    bool has_component()
    {
        return components.count(T::name());
    }

    void add_tag(std::string tag) 
    {
        tags.push_back(tag);
    }

    void remove_tag(std::string tag)
    {
        for(int i = 0; i < tags.size(); i++)
        {
            if(tags.at(i) == tag)
            {
                tags.erase(tags.begin() + i);
            }
        }
    }

    template <typename T, typename... TArgs>
    void add_script(TArgs&&... mArgs)
    {
        Script* new_script(new T(std::forward<TArgs>(mArgs)...));

        if(script_names.count(T::name()) == 1)
        {
            std::string message = "[WAR] Attempted to attach script: "
                + T::name() + " to entity: " + name + ", when an identical"
                " script already exists";
            Debug::log(message);
            return;
        }

        new_script->entity = this;
        script_names.emplace(T::name());

        scripts.push_back(new_script);

        if(scripts.size() == 1) 
        {
            EntityTracker::entities.push_back(this);
        }
    }

    std::string get_tag(std::string _tag)
    {
        for(std::string t : tags)
        {
            if(t == _tag) return t;
        }

        return std::string{};
    }

    template <typename T, typename... TArgs>
    T* add_component(TArgs&&... mArgs)
    {
        T* new_comp(new T(std::forward<TArgs>(mArgs)...));
        new_comp->entity = this;
        components[T::name()] = new_comp;

        return new_comp;
    }

    template<typename T>
    T* get_script() 
    {
        std::string script_name = T::name();

        if(script_names.count(script_name) == 0)
        {
            DEBUG_MESSAGE:

            std::string message = "[WAR] Entity.get_script -> Attempted to get"
                " script: " + script_name + " from entity: " + name + 
                ", when no matching script was found";
            Debug::log(message);
            return nullptr;
        }

        for(Script* s : scripts)
        {
            T* s_cast = dynamic_cast<T*>(s);

            if(s_cast != nullptr)
            {
                return s_cast;
            }
        }

        goto DEBUG_MESSAGE;

        return nullptr;
    }

    template<typename T>
    T* remove_script()
    {
        std::string script_name = T::name();

        if(script_names.count(script_name) == 0)
        {
            DEBUG_MESSAGE:

            std::string message = "[WAR] Attempted to delete script: " 
            + script_name + " from entity: " + name + ", but no script"
            " with that name was found";

            Debug::log(message);
            return nullptr;
        }

        script_names.erase(script_name);
        
        for(int i = 0; i < scripts.size(); i++)
        {
            Script* s_cast = dynamic_cast<T*>(scripts.at(i));

            script_name.erase(T::name());

            if(s_cast != nullptr)
            {
                scripts.erase(scripts.begin() + i);
                return s_cast;
            }
        }

        // for(int i = 0; i < scripts.size(); i++)
        // {
        //     if(scripts.at(i)->name() == script_name)
        //     {
        //         Script* targ_script = scripts.at(i);

        //         scripts.erase(scripts.begin() + i);

        //         if(scripts.size() == 0)
        //         {
        //             EntityTracker::remove_entity(this);
        //         }

        //         return static_cast<T*>(targ_script);
        //     }
        // }
    
        return nullptr;
    }

    template<typename T>
    T* get_component() const
    {
        std::string c_name = T::name();

        if(components.count(T::name()) == 0)
        {
            std::string message = "[WARN] Attempted to get " + 
                c_name + " from " + name + ", when no component exists "
                " on the entity";

            Debug::log(message);
            return nullptr;
        }

        return static_cast<T*>(components.at(c_name));
    }
    
    template<typename T>
    T* remove_component()
    {
        std::string comp_name = T::name();

        if(components.count(comp_name) == 0)
        {
            std::string message = "[WAR] Attempted to delete script: " 
            + comp_name + " from entity: " + name + ", but no script"
            " with that name was found";

            Debug::log(message);
            return nullptr;
        }


        T* targ_c = components.at(comp_name);

        components.erase(comp_name);

        return static_cast<T*>(targ_c);
    }

};

struct compare_entity_priority
{
    bool operator() (Entity* e_1, Entity* e_2)
    {
        SpriteComponent* s_component_1 = 
            e_1->get_component<SpriteComponent>();

        SpriteComponent* s_component_2 = 
            e_2->get_component<SpriteComponent>();

        //  static_cast<SpriteComponent*>(e_1->get_component(
        //         "SpriteComponent"));
            
        // SpriteComponent* s_component_2 = 
        //     static_cast<SpriteComponent*>(e_2->get_component(
        //         "SpriteComponent"));

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

    EntityHandler() 
    {
        width = 0; 
        height = 0;
    }

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
        for(Entity* e : EntityTracker::entities)
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

