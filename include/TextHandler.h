#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <map>
#include <string>

#include "TextureHandler.h"
#include "DisplayCharacter.h"

struct CharacterID
{
    int src_x;
    int src_y;

    CharacterID()
    {
        src_x = 0;
        src_y = 0;
    }

    CharacterID(int _src_x, int _src_y)
    {
        src_x = _src_x;
        src_y = _src_y;
    }

    ~CharacterID() {}
};

class TextHandler
{

public:

    TextHandler();
    TextHandler(TextureHandler* _texture_handler);
    ~TextHandler();

    bool contains(int c);

    void load_font(const char* path);
    void add(int symbol, int x_pos, int y_pos, std::string color);
    void add(DisplayCharacter display_char, int x_pos, int y_pos);
    void draw();
    void clear();
    void set_draw_start_position(int _draw_start_position);
    void modify_font_multiplier(float delta);

    int get_font_width();
    int get_font_height();
    
    float get_font_size_multiplier();

private:

    int font_width;
    int font_height;

    int draw_start_position = 0;

    float font_size_multiplier = 2.0;

    SDL_Texture* character_sprites;
    std::map<std::string, CharacterID> character_data;

    TextureHandler* texture_handler;

    std::map<std::pair<int,int>, DisplayCharacter> content;
};
