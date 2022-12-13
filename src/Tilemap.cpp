#include <algorithm>

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
    edge_map_collider->add_component<SpriteComponent>('S', "LGRAY", 5);
    edge_map_collider->add_component<ColliderComponent>();
    edge_map_collider->add_tag("NON_TRAVERSABLE");

    for(int x = 0; x < width; x++)
    {
        add_copy_entity(edge_map_collider, x, 0);
        add_copy_entity(edge_map_collider, x, height - 1);
    }

    for(int y = 0; y < height; y++)
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

    else
    {
        e->get_component<TransformComponent>()->set_position(x, y);
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
    if(!e->has_component<TransformComponent>())
    {
        Debug::log("[ERR] Tilemap.remove_entity -> Entity does not have"
            "required Transform Component");
        exit(0);
    }

    TransformComponent* t_component = 
        e->get_component<TransformComponent>();

    if(!entity_handler->remove_entity(e, t_component->x_pos, 
        t_component->y_pos))
    {
        Debug::log("[ERR] Tilemap.remove_entity -> Could not remove" 
            "entity");
        exit(0);
    }
}

void Tilemap::fill_tilemap(Entity* e)
{
    TransformComponent* t_component = 
        e->get_component<TransformComponent>();

    int initial_x = t_component->x_pos;
    int initial_y = t_component->y_pos;

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(x != initial_x || y != initial_y)
            {
                add_copy_entity(e, x, y);
            }
        }
    }
}

int Tilemap::get_width() { return width; }

int Tilemap::get_height() { return height; }

std::vector<DisplayCharacter> Tilemap::get_display(int start_x, int start_y,
    int end_x, int end_y)
{
    std::vector<DisplayCharacter> visible_characters;

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
                visible_characters.push_back(DisplayCharacter(
                    '%', "WHITE" 
                ));
                continue;
            }



            SpriteComponent* s_component = 
                entities_at_position.front() ->
                get_component<SpriteComponent>();

            visible_characters.push_back(DisplayCharacter(
                s_component->symbol, s_component->color
            ));
        }

        visible_characters.push_back(DisplayCharacter('\n', "WHITE"));
    }

    return visible_characters;
}

std::list<Entity*> Tilemap::get_entities_at_position(int x, int y)
{
    return entity_handler->get_entities_at_position(x, y);
}

EntityHandler* Tilemap::get_entity_handler() { return entity_handler; }


// ___________________________TilemapHandler___________________________________

Tilemap* TilemapHandler::active_tilemap = nullptr;
