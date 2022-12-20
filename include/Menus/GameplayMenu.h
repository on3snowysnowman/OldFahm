#pragma once 

#include "Menu.h"
#include "Tilemap.h"
#include "Windows/TilemapWindow.h"
#include "TextureHandler.h"
#include "InputHandler.h"

class GameplayMenu : public Menu
{

public:

    GameplayMenu(MenuHandler* _menu_handler, InputHandler* input_handler,
        TextureHandler* texture_handler, Tilemap* _tilemap, int start_x, 
        int start_y, int end_x, int end_y);

    void update() override;
    void render() override;
    void start() override;

    void init_tilemap();

private:

    Tilemap* tilemap;

    TilemapWindow* tilemap_window;

};

