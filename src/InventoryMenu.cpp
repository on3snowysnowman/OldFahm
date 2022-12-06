#include "Menus/InventoryMenu.h"


// Constructors / Deconstructor

InventoryMenu::InventoryMenu(InputHandler* _input_handler)
{
    name = "InventoryMenu";

    windows.push_back(full_window);

    input_handler = _input_handler;

    full_window = new BaseWindow(MenuData::texture_handler, 0, 0, 
        MenuData::screen_width, MenuData::screen_height, false);
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

                MenuData::deactivate_menu(this);
                input_handler->set_delay(SDLK_ESCAPE, -1);
                break;
        }
    }
}

void InventoryMenu::render()
{
    full_window->clear_content();
    full_window->add_str("This is the inventory window");
    full_window->render();
}
