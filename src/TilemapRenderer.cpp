#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>

#include "TilemapRenderer.h"
#include "Jloader.h"


// Constructors / Deconstructor

TilemapRenderer::TilemapRenderer(TextureHandler* _texture_handler)
{
    texture_handler = _texture_handler;
    load_tile_textures("data/textureData/ojae_default_texture.json");
}


// Public Members

void TilemapRenderer::clear()
{
    tiles_to_render.clear();
}

void TilemapRenderer::add(int x_pos, int y_pos, TileID tile_id)
{
    tiles_to_render.push_back(std::pair<Coordinate, TileID> 
        {Coordinate(x_pos, y_pos), tile_id});
}

void TilemapRenderer::draw()
{
    for(std::vector<std::pair<Coordinate, TileID>>::iterator it = 
        tiles_to_render.begin(); it != tiles_to_render.end();
        it++)
    {
        SDL_Rect src, dest;

        src.x = (it->second % num_tiles_per_row_in_texture) * tile_size;
        src.y = int(it->second / num_tiles_per_row_in_texture) * tile_size;
        src.w = tile_size;
        src.h = tile_size;

        dest.x = it->first.x;
        dest.y = it->first.y;
        dest.w = tile_size * 2;
        dest.h = tile_size * 2;

        texture_handler->draw(tiles_texture, src, dest);
    }
}

int TilemapRenderer::get_tile_size() { return tile_size * tile_size_modifier; }


// Private Members

void TilemapRenderer::load_tile_textures(const char* json_path)
{
    if(!Debug::file_exists(json_path))
    {
        std::string message = "[ERR] TilemapRenderer.load_tile_textures("
            "const char* json_path where \"json_path\" = " + 
            std::string{json_path} + " -> No file directory exists.";

        Debug::log(message);
        exit(0);
    }

    nlohmann::json json_obj = Jloader::get(json_path);

    tile_size = json_obj["tile_size"];
    num_tiles_per_row_in_texture = json_obj["tiles_per_row"];

    std::string texture_path = json_obj["texture_path"];

    tiles_texture = texture_handler->load_texture(texture_path.c_str());

}
