#pragma once

#include "Tilemap.h"

class TilemapLoader
{

public:

    static void save_tilemap(const char* path, Tilemap* tilemap);
    
    static Tilemap* load_tilemap(const char* path);

private:

};
