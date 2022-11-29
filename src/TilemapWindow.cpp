#include "Windows/TilemapWindow.h"


// Constructors / Deconstructor

TilemapWindow::TilemapWindow()
{
    tilemap = nullptr;

    Debug::log("[WARN] TilemapWindow.TilemapWindow -> Called by default"
    " constructor, initialized null pointer for tilemap pointer");
}

TilemapWindow::TilemapWindow(TextureHandler* _texture_handler, 
    Tilemap* _tilemap, int _start_x, int _start_y, int _end_x, int _end_y) : 
    BaseWindow(_texture_handler, _start_x, _start_y, _end_x, _end_y, false)
{
    tilemap = _tilemap;
}

TilemapWindow::~TilemapWindow() {}


// Public Members 

void TilemapWindow::update()
{
    tilemap->update();
}

void TilemapWindow::render()
{
    clear_content();

    draw_border();

    for(DisplayCharacter c : tilemap->get_display(0, 0, 14, 
        14))
    {
        add_ch(int(c.symbol), c.color);
        
        if(c.symbol != '\n') add_ch(' ');
        
    }

    text_handler->draw();
}

