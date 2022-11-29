#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>
#include <vector>

#include "Color.h"

class TextureHandler
{

private:

    SDL_Renderer* renderer; // Instance of the renderer

    /**
     * @brief  Map of Color names to registered colors
     */
    std::map<std::string, Color*> colors;

public:

    TextureHandler();
    TextureHandler(SDL_Renderer* renderer);
    ~TextureHandler();

    /**
     * @brief Loads a png image from a directory and converts it into an SDL
     * Texture
     * @param path Directory of the png image
     * @return SDL_Texture* */
    SDL_Texture* load_texture(const char* path);

    std::vector<std::string> get_colors();

    /**
     * @brief Adds a color to the map of registered colors
     * 
     * @param color Color to add
     */
    void add_color(Color* color);

    /**
     * @brief Loads a texture into the renderer to be drawn.
     * @param texture Texture to be drawn
     * @param src Source Rect for rendering
     * @param dest Destination Rect for rendering
     * @param color Name of the registered color to apply to the texture, 
     *     use empty string to leave texture unnaffected
     * */
    void draw(SDL_Texture* texture, SDL_Rect& src, SDL_Rect& dest, 
        std::string color = "");

};