#include "Menus/InventoryMenu.h"
#include "Tilemap.h"

// Constructors / Deconstructor

InventoryMenu::InventoryMenu(InputHandler* _input_handler,
    StorageComponent* _player_storage_component)
{
    name = "InventoryMenu";

    player_storage_component = _player_storage_component;

    windows.push_back(full_window);

    input_handler = _input_handler;

    full_window = new BaseWindow(MenuManager::texture_handler, 0, 0, 
        MenuManager::screen_width, MenuManager::screen_height, false);
}

InventoryMenu::~InventoryMenu()
{
    delete full_window;
}


// Public members

void InventoryMenu::update()
{
    std::vector<Key*> keys = input_handler->get_active_keys();

    for(Key* k : keys)
    {
        switch(k->id)
        {
            case SDLK_ESCAPE:

                MenuManager::deactivate_menu(this);
                input_handler->set_delay(SDLK_ESCAPE, -1);
                break;
        }
    }
}

void InventoryMenu::render()
{
    full_window->clear_content();
    full_window->add_str("Inventory:\n\n");

    for(Entity* e : player_storage_component->stored_entities)
    {
        SpriteComponent* s_comp = e->get_component<SpriteComponent>();

        full_window->add_str(e->name, s_comp->color);
        full_window->add_ch('\n');
    }

    full_window->render();
}
