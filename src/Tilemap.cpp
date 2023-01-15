#include <algorithm>
#include <fstream>

#include "Debug.h"
#include "Tilemap.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/ColliderComponent.h"


// Constructors / Deconstructor

Tilemap::Tilemap()
{
    Debug::log("[ERR] Tilemap.DefaultConstructor -> Width or height is less "
        "than 3, Tilemap is too small");
    exit(0);

    entity_handler = nullptr;
    width = 0;
    height = 0;
}

Tilemap::Tilemap(int _width, int _height)
{

    if(_width < 3 || _height < 3)
    {
        Debug::log("[ERR] Tilemap.FirstConstructor -> Width or height is less "
        "than 3, Tilemap is too small");
        exit(0);
    }

    entity_handler = new EntityHandler(_width, _height);
    width = _width;
    height = _height;

    Entity* edge_map_collider = new Entity("EDGE MAP COLLIDER");
    edge_map_collider->add_component<TransformComponent>(0, 0);
    edge_map_collider->add_component<SpriteComponent>();
    edge_map_collider->add_component<ColliderComponent>();
    edge_map_collider->add_tag("NON_TRAVERSABLE");

    for(int x = 0; x < width; x++)
    { 
        add_copy_entity(edge_map_collider, x, 0);
        add_copy_entity(edge_map_collider, x, height - 1);
    }

    for(int y = 1; y < height - 1; y++)
    {
        add_copy_entity(edge_map_collider, 0, y);
        add_copy_entity(edge_map_collider, width - 1, y);
    }

}

Tilemap::~Tilemap()
{
    delete entity_handler;
}


// Public Members

void Tilemap::_output_tilemap_to_file(const char* path)
{
    std::fstream file_stream;

    file_stream.open(path, std::ios::out);

    if(file_stream.is_open())
    {
        for(std::pair<std::pair<int,int>, std::list<Entity*>> _pair : 
            entity_handler->get_all_entities())
        {
            for(Entity* e : _pair.second)
            {
                TransformComponent* e_t_comp = 
                    e->get_component<TransformComponent>();

                file_stream << '(' << _pair.first.first << ", " << 
                    _pair.first.second << "): " << e->name << 
                    " -> T Component(" << e_t_comp->x_pos << ", "
                    << e_t_comp->y_pos << ")\n";
            }
        }

        file_stream.close();
    }

    file_stream.clear();

}

void Tilemap::update()
{
    entity_handler->update();
}

void Tilemap::add_entity(Entity* e, int x, int y)
{
    if(!e->has_component<TransformComponent>())
    {
        e->add_component<TransformComponent>(x, y);
    }
    
    entity_handler->add_entity(e, x, y);
}

void Tilemap::add_copy_entity(Entity* e, int x, int y)
{
    Entity* copy_e = new Entity(*e);
    add_entity(copy_e, x, y);
}

void Tilemap::remove_entity(Entity* e)
{
    if(!entity_handler->remove_entity(e))
    {
        std::string message = "[ERR] Tilemap.remove_entity(Entity* e) where" 
            "\"e\" is" + e->name +  "-> Could not remove entity";

        Debug::log(message);
        exit(0);
    }
}

void Tilemap::remove_entity_by_name_at_pos(std::string name, int x, int y)
{
    std::list<Entity*> entities_at_pos = 
        entity_handler->get_entities_at_position(x, y);

    for(std::list<Entity*>::iterator it = entities_at_pos.begin(); 
        it != entities_at_pos.end(); it++)
    {
        if((*it)->name == name)
        {
            entity_handler->remove_entity((*it));
            return;
        }
    }

    std::string message = "[WAR] Tilemap.remove_entity_by_name_at_pos"
        "(std::string name, int x, int y) where \"name\" == " + name +
        ", \"x\" = " + std::to_string(x) + "\"y\" = " + std::to_string(y)
        + " -> Could not find specified entity at position";

    Debug::log(message);
}

void Tilemap::find_and_remove_entity_by_name(std::string name)
{

}

void Tilemap::fill_tilemap(Entity* e)
{
    add_entity(e, 0, 0);

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(x != 0 || y != 0)
            {
                add_copy_entity(e, x, y);
            }
        }
    }
}

int Tilemap::get_width() { return width; }

int Tilemap::get_height() { return height; }

std::vector<TileID> Tilemap::get_display(int start_x, int start_y,
    int end_x, int end_y)
{
    std::vector<TileID> visible_tiles;

    for(int y = start_y; y <= end_y; y++)
    {
        for(int x = start_x; x <= end_x; x++)
        {
            std::list<Entity*> entities_at_position =
                entity_handler->get_entities_at_position(x, y);

            if(entities_at_position.size() == 0 || 
                !entities_at_position.front()->
                has_component<SpriteComponent>())
            {
                visible_tiles.push_back(NO_ID);

                // visible_characters.push_back(DisplayCharacter(
                //     '%', "WHITE" 
                // ));
                continue;
            }

            SpriteComponent* s_component = 
                entities_at_position.front() ->
                get_component<SpriteComponent>();
            visible_tiles.push_back(s_component->tile_id);

            // visible_characters.push_back(DisplayCharacter(
            //     s_component->tile_id, s_component->color
            // ));
        }

        // visible_characters.push_back(DisplayCharacter('\n', "WHITE"));
    }

    return visible_tiles;
}

std::list<Entity*> Tilemap::get_entities_at_position(int x, int y)
{
    return entity_handler->get_entities_at_position(x, y);
}

EntityHandler* Tilemap::get_entity_handler() { return entity_handler; }
