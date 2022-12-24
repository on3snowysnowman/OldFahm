#pragma once

#include "Menu.h"
#include "../InputHandler.h"
#include "../Windows/BaseWindow.h"
#include "../Windows/TilemapWindow.h"
#include "../Components/StorageComponent.h"

class InventoryMenu : public Menu
{

public:

    InventoryMenu(MenuHandler* _menu_handler, InputHandler* _input_handler,     
        TextureHandler* _texture_handler, StorageComponent* _player_inventory, 
        int start_x, int start_y, int end_x, 
        int end_y);
    
    void update() override;
    void render() override;
    void start() override;

private:

    BaseWindow* inventory_window;
    
    TilemapWindow* tilemap_window;

    StorageComponent* player_inventory;
};
