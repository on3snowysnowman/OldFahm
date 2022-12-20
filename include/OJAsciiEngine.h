#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>

#include "TextureHandler.h"
#include "InputHandler.h"
#include "Entity.h"

namespace ojae
{

class OJAsciiEngine
{

public:

    /**
     * @brief OJAsciiEngine Constructor
     * 
     * @param title Title of the Window
     */
    OJAsciiEngine(const char* title);
    ~OJAsciiEngine();

protected:

    SDL_Window* window;

    SDL_Renderer* renderer;
    SDL_Event event;

    bool running;

    const int TARG_FPS = 60;

    const int FRAME_DELAY = 1000 / TARG_FPS;

    int frame_time; // Amount of time the last frame took

    int screen_width; // Width of the screen
    int screen_height; // Height of the screen

    Uint64 frame_start; // TIme stamp of when the current frame started

    /**
     * @brief Font names to their specified font paths
     * 
     */
    std::unordered_map<std::string, std::string> fonts;

    InputHandler* input_handler;

    TextureHandler* texture_handler;

    void start_OJAE();
    void simulation_loop(); 
    void clear_screen();
    void draw_to_screen();
    void set_key_delay(int key, int frames = 14);
    virtual void update();
    virtual void render();
    virtual void quit();

    std::vector<int> get_pressed_keys();
    
private:

    void handle_events();
    // void get_fonts(const char* path);
    void load_colors(const char* path);

};

}

