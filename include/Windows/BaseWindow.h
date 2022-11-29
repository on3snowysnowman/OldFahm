#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string> 

#include "../TextHandler.h"
#include "../TextureHandler.h"

/**
 * @brief Modular window for displaying text to the screen
 * 
 */
class BaseWindow
{

public:

    BaseWindow();
    BaseWindow(TextureHandler* _texture_handler, int _start_x, int _start_y,
        int _end_x, int _end_y, bool _focused);
    ~BaseWindow();

    void load_font(std::string path);
    void resize_window(int start_x, int start_y, int end_x, int end_y);
    void focus_window();
    void unfocus_window();
    void add_ch(int c, std::string color = "WHITE");
    void add_str(std::string _str, std::string color = "WHITE");
    void add_new_line(int num_new_line = 1);
    void clear_content();
    void set_cursor_pos(int x, int y);

    virtual void update();
    virtual void render();

protected:

    bool focused;

    int cursor_x_pos;
    int cursor_y_pos;

    int border_size;

    int start_x;
    int start_y;
    int end_x;
    int end_y;

    SDL_Rect border_src;

    SDL_Rect top_border;
    SDL_Rect right_border;
    SDL_Rect bottom_border;
    SDL_Rect left_border;

    SDL_Texture* border;
    SDL_Texture* border_selected;
    SDL_Texture* font_texture;

    TextHandler* text_handler;
    TextureHandler* texture_handler;

    void draw_border();

};