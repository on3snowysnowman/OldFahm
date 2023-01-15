#include <nlohmann/json.hpp>
#include <map>
#include <list>

#include "TilemapLoader.h"
#include "Jloader.h"

void TilemapLoader::save_tilemap(const char* path, Tilemap* tilemap)
{
    nlohmann::json tilemap_save;

    tilemap_save["width"] = tilemap->get_width();
    tilemap_save["height"] = tilemap->get_width();

    std::map<std::pair<int, int>, std::list<Entity*>> entity_positions;

    for(std::map<std::pair<int,int>, std::list<Entity*>>::iterator it = 
        entity_positions.begin(); it != entity_positions.end(); it++)
    {
        for(Entity* e : it->second)
        {
            
        }
    }
}

Tilemap* TilemapLoader::load_tilemap(const char* path)
{

}