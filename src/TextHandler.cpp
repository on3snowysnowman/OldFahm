#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>
#include <iostream>

#include "TextHandler.h"
#include "Debug.h"
#include "Jloader.h"

// Constructors / Deconstructors

TextHandler::TextHandler()
{
    texture_handler = nullptr;
}

TextHandler::TextHandler(TextureHandler* _texture_handler)
{

    texture_handler = _texture_handler;
}

TextHandler::~TextHandler() {}


// Public Functions 

void TextHandler::load_font(const char* path)
{
    if(!Debug::file_exists(path))
    {
        Debug::log("[ERR] TextHandler.load_font -> Could not open file: ", 
            false, true);
        Debug::log(path, false, false);
        exit(0);
    }

    nlohmann::json json_obj;

    json_obj = Jloader::get(path);

    character_sprites = texture_handler->load_texture(std::string(json_obj["font_png_path"]).c_str());

    font_width = json_obj["font_width"];
    font_height = json_obj["font_height"];

    json_obj = Jloader::get(std::string(json_obj["font_data_path"]).c_str());

    for(nlohmann::json::iterator it = json_obj.begin(); it != json_obj.end();
        it++)
    {
        character_data.emplace(it.key(), CharacterID(it.value().at(0),
            it.value().at(1)));
    }
}

void TextHandler::add(int symbol, int x_pos, int y_pos, std::string color)
{
    content[{x_pos, y_pos}] = DisplayCharacter(symbol, color);
}

void TextHandler::add(DisplayCharacter display_char, int x_pos, int y_pos)
{
    content[{x_pos, y_pos}] = display_char;
}

void TextHandler::draw()
{
    // std::cout << "Draw start: " << draw_start_position << '\n';

    for(std::map<std::pair<int,int>, DisplayCharacter>::iterator it = content.begin();
        it != content.end(); it++)
    {
        SDL_Rect src, dest;

        int c = it->second.symbol;

        src.x = character_data[std::to_string(c)].src_x;
        src.y = character_data[std::to_string(c)].src_y;
        src.w = font_width;
        src.h = font_height;

        dest.x = it->first.first;
        dest.y = it->first.second - draw_start_position;
        dest.w = src.w * 2;
        dest.h = src.h * 2;

        texture_handler->draw(character_sprites, src, dest, it->second.color);
    }
}

void TextHandler::clear()
{
    content.clear();
    draw_start_position = 0;
}

void TextHandler::set_draw_start_position(int _draw_start_position)
{
    draw_start_position = _draw_start_position;
}

int TextHandler::get_font_width() { return font_width; }

int TextHandler::get_font_height() { return font_height; }

bool TextHandler::contains(int c)
{
    if(character_data.count(std::to_string(c)) != 0) return true;
    return false; 
}


// Private Functions

