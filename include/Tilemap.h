#pragma once

#include <map>
#include <vector>

#include "Entity.h"
#include "Debug.h"
#include "DisplayCharacter.h"
#include "TileID.h"

class Tilemap
{

public:

    Tilemap();
    Tilemap(int _width, int _height);
    ~Tilemap();

    void update();
    void add_entity(Entity* e, int x, int y);
    void add_copy_entity(Entity* e, int x, int y);
    void remove_entity(Entity* e);
    void fill_tilemap(Entity* e);

    int get_width();
    int get_height();

    std::vector<TileID> get_display(int start_x, int start_y,
        int end_x, int end_y);
    std::list<Entity*> get_entities_at_position(int x, int y);
    
    EntityHandler* get_entity_handler();

private:

    int width;
    int height;
    
    EntityHandler* entity_handler;
};

