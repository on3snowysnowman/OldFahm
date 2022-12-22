#pragma once 

#include "Menu.h"
#include "../Tilemap.h"
#include "../Windows/BaseWindow.h"
#include "../Windows/TilemapWindow.h"
#include "../TextureHandler.h"
#include "../InputHandler.h"


class TileDisplayMenu : public Menu
{

public:

    TileDisplayMenu(MenuHandler* _menu_handler, InputHandler* _input_handler, 
        TextureHandler* _texture_handler, int start_x, 
        int start_y, int end_x, int end_y);

    void update() override;
    void render() override;
    void start() override;


private:

    Entity* cursor;

    Tilemap* tilemap;

    TilemapWindow* tilemap_window;
};