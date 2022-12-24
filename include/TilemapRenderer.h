#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <map>

#include "Tilemap.h"
#include "TextureHandler.h"
#include "Coordinate.h"
#include "TileID.h"

class TilemapRenderer
{

public:

    TilemapRenderer(TextureHandler* _texture_handler);

    void clear();
    void add(int x_pos, int y_pos, TileID tile_id);
    void draw();

    int get_tile_size();

private:

    int tile_size; 
    int tile_size_modifier = 2;

    int num_tiles_per_row_in_texture;

    SDL_Texture* tiles_texture;

    TextureHandler* texture_handler;

    std::vector<std::pair<Coordinate, TileID>> tiles_to_render;

    void load_tile_textures(const char* json_path);

};
