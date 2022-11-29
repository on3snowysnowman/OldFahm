#include <iostream>
#include <fstream>

#include "TextureHandler.h"
#include "Debug.h"

// Constructors/Deconstructors

TextureHandler::TextureHandler()
{
    renderer = nullptr;
}

TextureHandler::TextureHandler(SDL_Renderer* _renderer)
{
    renderer = _renderer;
}

TextureHandler::~TextureHandler() {}

// Public Functions

SDL_Texture* TextureHandler::load_texture(const char* path)
{

    try
    {
        if(!Debug::file_exists(path))
        {
            throw path;
        }
    }

    catch(const char* path)
    {
        Debug::log("[ERR] TextureHandler.load_texture -> Could not open"
            " file: ", false, true);
        Debug::log(path, false, false);
        exit(0);
    }

    SDL_Surface* temp_surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);

    SDL_FreeSurface(temp_surface);

    return texture;
}

void TextureHandler::add_color(Color* color)
{
    colors.emplace(color->get_name(), color);
}

std::vector<std::string> TextureHandler::get_colors()
{ 
    std::vector<std::string> color_names;

    for(std::pair<std::string, Color*> element : colors)
    {
        color_names.push_back(element.first);
    } 

    return color_names;
}

void TextureHandler::draw(SDL_Texture* texture, SDL_Rect& src, SDL_Rect& dest,
    std::string color)
{
    if(color.size() != 0)
    {
        // If the color doesn't exist in the registered colors map
        if(colors.count(color) == 0)
        {
            Debug::log("[FAIL] TextureHandler.draw() -> Color not "
                "registered: ", false, true);
            Debug::log(color, false, false);
            exit(0);
        }

        Color* targ_color = colors[color];

        SDL_SetTextureColorMod(texture, targ_color->get_r(), 
            targ_color->get_g(),targ_color->get_b());
    }

    SDL_RenderCopy(renderer, texture, &src, &dest);
}