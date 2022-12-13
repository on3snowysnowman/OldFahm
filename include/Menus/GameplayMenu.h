#pragma once

#include "Menu.h"
#include "Tilemap.h"
#include "../Entity.h"
#include "../InputHandler.h"
#include "../Windows/BaseWindow.h"
#include "../Windows/TilemapWindow.h"

class GameplayMenu : public Menu
{

public:

    GameplayMenu(InputHandler* _input_handler);
    ~GameplayMenu();

    void update() override;
    void render() override;

    Entity* get_player();

private:

    InputHandler* input_handler;

    Tilemap* tilemap;

    BaseWindow* tile_display_window;
    TilemapWindow* tilemap_window;

    Entity* player;

    Entity* create_entity(int x_pos, int y_pos, int rendering_priority, 
        char symbol, std::string name, std::string color, bool add_collider);
};
