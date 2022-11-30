#include <iostream>

#include "Windows/BaseWindow.h"
#include "Debug.h"

// Constructors / Deconstructor

BaseWindow::BaseWindow()
{
    resize_window(0, 0, 0, 0);
    focused = false;
    texture_handler = nullptr;
    text_handler = nullptr;

    Debug::log("[WARN] BaseWindow.BaseWindow -> BaseWindow is uninitialized"
        " and is declared with null pointers");
}

BaseWindow::BaseWindow(TextureHandler* _texture_handler, int _start_x, 
    int _start_y, int _end_x, int _end_y, bool _focused)
{
    resize_window(_start_x, _start_y, _end_x, _end_y);
    focused = _focused;
    texture_handler = _texture_handler;

    border = texture_handler->load_texture("assets/Sprites/border.png");
    border_selected = texture_handler->load_texture("assets/Sprites/border_selected.png");
    text_handler = new TextHandler(_texture_handler);

    set_cursor_pos(0, 0);

    load_font("data/fonts/ojae/ojae_font_data.json");
}

BaseWindow::~BaseWindow()
{
    delete text_handler;
}


// Public Members

void BaseWindow::load_font(std::string path)
{
    text_handler->load_font(path.c_str());
}

void BaseWindow::resize_window(int start_x, int start_y, int end_x, 
    int end_y)
{
    border_size = 8;

    // Reset window dimensions with respect for border room
    this->start_x = start_x + border_size + 8;
    this->end_x = end_x - border_size - 8;
    this->start_y = start_y + border_size + 8;
    this->end_y = end_y - border_size - 8;

    // Establish Border Image Source dimensions
    border_src.x = 0;
    border_src.y = 0;
    border_src.w = 1;
    border_src.h = 1;

    // Establish Top Border dimensions
    top_border.x = start_x;
    top_border.y = start_y;
    top_border.w = end_x - start_x;
    top_border.h = border_size;

    // Establish Right Border dimensions
    right_border.x = end_x - border_size;
    right_border.y = start_y;
    right_border.w = border_size;
    right_border.h = end_y;

    // Establish Bottom Border dimensions
    bottom_border.x = start_x;
    bottom_border.y = end_y - border_size;
    bottom_border.w = end_x - start_x;
    bottom_border.h = border_size;

    // Establish Left Border Dimensions
    left_border.x = start_x;
    left_border.y = start_y;
    left_border.w = border_size;
    left_border.h = end_y;
}

void BaseWindow::focus_window()
{
    focused = true;
}

void BaseWindow::unfocus_window()
{
    focused = false;
}

void BaseWindow::add_ch(int c, std::string color)
{
    int font_width = text_handler->get_font_width();
    int font_height = text_handler->get_font_height();
    int window_width = end_x - border_size;

    if(c == ' ')
    {
        goto BEFORE_INCREMENT_CURSOR_X;
    }

    if(c == '\n')
    {
        cursor_x_pos = start_x;
        cursor_y_pos += font_height * 1.5;
        return;
    }

    if(!text_handler->contains(c))
    {
        Debug::log("[ERR] SDLHandler.add_ch -> CharacterID : ", false, true);
        Debug::log(c, false, false);
        Debug::log(" not found in character font data", false, false);
        exit(0);
    }

    text_handler->add(c, cursor_x_pos, cursor_y_pos, color);

    BEFORE_INCREMENT_CURSOR_X:

    if(cursor_x_pos + font_width > 
        window_width - font_width)
    {
        add_new_line();
    }

    cursor_x_pos += font_width;
}

void BaseWindow::add_str(std::string _str, std::string color)
{
    int font_width = text_handler->get_font_width();
    int font_height = text_handler->get_font_height();
    int window_width = end_x;

    // If the string is larger than the empty space between the cursor x position
    // and the border of the window

    // if(cursor_x_pos + (_str.size() * font_width) > end_x - border_size - 1)
    // {
    //     int i = 0;

    //     while(i < int((end_x - border_size - cursor_x_pos) / 
    //         font_width))
    //     {
    //         add_ch(_str.at(i), color);

    //         i++;
    //     }

    //     add_ch('\n');

    //     while(i < _str.size())
    //     {
    //         add_ch(_str.at(i)), color;

    //         i++;
    //     }

    //     return;
    // }

    std::string current_word;

    int i = 0;

    int bound = _str.size();

    while(i < bound)
    {
        if(cursor_x_pos + font_width > 
            window_width - font_width)
        {
            add_new_line();
        }

        if(_str.at(i) == '\n')
        {
            for(char c : current_word)
            {
                add_ch(int(c), color);
            }

            add_new_line();
            
            current_word.clear();
            i++;
            continue;
        }

        else if(_str.at(i) == ' ')
        {
            for(char c : current_word)
            {
                add_ch(int(c), color);
            }

            add_ch(' ');

            current_word.clear();
            i++;
            continue;
        }

        current_word.push_back(_str.at(i));
        i++;
    }

    for(char c : current_word)
    {
        add_ch(int(c), color);
    }

}

void BaseWindow::add_new_line(int num_new_line)
{
    if(num_new_line <= 0) { return; }

    cursor_x_pos = start_x;
    cursor_y_pos += ((text_handler->get_font_height()) * 1.5) * 
        num_new_line;
    // update_draw_position(cursor_y_pos);
}

void BaseWindow::clear_content()
{
    cursor_x_pos = start_x;
    cursor_y_pos = start_y;

    text_handler->clear();
}

void BaseWindow::set_cursor_pos(int x, int y)
{
    // Set them in relation to the start of the window, rather than the start
    // of the screen

    cursor_x_pos = x + start_x;
    cursor_y_pos = y + start_y;
}

void BaseWindow::zoom_in() 
{
    float font_size_multiplier = text_handler->get_font_size_multiplier();

    if(font_size_multiplier < 2.0)
    {
        text_handler->modify_font_multiplier(0.2);
    }
}

void BaseWindow::zoom_out() 
{
    float font_size_multiplier = text_handler->get_font_size_multiplier();

    if(font_size_multiplier > 1.0)
    {
        text_handler->modify_font_multiplier(-0.2);
    }
}

void BaseWindow::update() {}

void BaseWindow::render() 
{
    draw_border();

    for(Text t : text_to_render)
    {
        add_str(t.content, t.color);
        add_new_line();
    }

    text_to_render.clear();

    text_handler->draw();
}


// Protected Members

void BaseWindow::draw_border()
{
    SDL_Texture* targ_texture = border;

    if(focused)
    {
        targ_texture = border_selected;
    }

    //Draw Borders 
    texture_handler->draw(targ_texture, border_src, top_border);
    texture_handler->draw(targ_texture, border_src, right_border);
    texture_handler->draw(targ_texture, border_src, bottom_border);
    texture_handler->draw(targ_texture, border_src, left_border);
}
