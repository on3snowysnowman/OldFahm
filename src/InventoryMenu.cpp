#include "Menus/InventoryMenu.h"
#include "Menus/GameplayMenu.h"
#include "Components/SpriteComponent.h"


// Constructors / Deconstructor

InventoryMenu::InventoryMenu(MenuHandler* _menu_handler, 
    InputHandler* _input_handler, TextureHandler* _texture_handler, 
    StorageComponent* _player_inventory, int start_x, int start_y, 
    int end_x, int end_y) : 
    Menu(_menu_handler, _input_handler, _texture_handler)
{
    inventory_window = new BaseWindow(_texture_handler, int((end_x - start_x) / 2),
        start_y, end_x, end_y, false);

    GameplayMenu* gameplay_menu = static_cast<GameplayMenu*>(
        menu_handler->get_menu(GAMEPLAY));
    
    tilemap_window = gameplay_menu->get_tilemap_window();

    player_inventory = _player_inventory;

    menu_id = INVENTORY;
}


// Public Members

void InventoryMenu::update()
{
    inventory_window->clear_content();

    inventory_window->add_str("Inventory:\n\n");

    // for(Entity* e : player_inventory->stored_entities)
    // {
    //     SpriteComponent* targ_e_s_comp = e->get_component<
    //         SpriteComponent>();

    //     inventory_window->add_str(e->name, targ_e_s_comp->color);
    //     inventory_window->add_new_line();

    // }

    for(std::pair<Text, int> _pair : player_inventory->get_storage_display())
    {
        inventory_window->add_str(_pair.first.content, _pair.first.color);
        inventory_window->add_str(" x" + std::to_string(_pair.second));
        inventory_window->add_new_line();
    }

    std::vector<Key*> active_keys = input_handler->get_active_keys();

    if(active_keys.size() == 0) return;

    switch(active_keys.at(0)->id)
    {
        case SDLK_i:

            input_handler->set_delay(SDLK_i, -1);
            menu_handler->deactivate_active_menu();
            break;
    }
}

void InventoryMenu::render()
{
    tilemap_window->render();
    inventory_window->render();
}

void InventoryMenu::start()
{

}
