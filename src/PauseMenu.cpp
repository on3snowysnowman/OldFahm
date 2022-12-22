#include "Menus/PauseMenu.h"
#include "EventQueue.h"

// Constructors / Deconstructor

PauseMenu::PauseMenu(MenuHandler* _menu_handler,
    InputHandler* _input_handler, TextureHandler* _texture_handler, 
    int start_x, int start_y, int end_x, int end_y) : 
    Menu(_menu_handler, _input_handler, _texture_handler)
{
    cursor_color = "BLUE";

    full_window = new BaseWindow(texture_handler, start_x, start_y, 
        end_x, end_y, true);

    menu_tools = new MenuTools(full_window, input_handler);

    menu_id = PAUSE;
}


// Public Members

void PauseMenu::update()
{

    for(Key* k : input_handler->get_active_keys())
    {
        if(k->id == SDLK_ESCAPE)
        {
            menu_handler->deactivate_active_menu();
            input_handler->set_delay(SDLK_ESCAPE, -1);
            return;
        }
    }

    std::vector<Text> choices 
    {
        Text("Resume"),
        Text("Exit")
    };
    

    sel_last_iteration = menu_tools->simulate_list_selection("Make a selection", 
        choices, sel_last_iteration.first, cursor_color);

    if(sel_last_iteration.second)
    {
        switch(sel_last_iteration.first)
        {
            
            // Resume

            case 0:

                menu_handler->deactivate_active_menu();
                return;

            // Exit

            case 1: 

                EventQueue::place_event("QUIT");
                return;

        }
    }
}

void PauseMenu::render()
{
    menu_tools->render();
}

void PauseMenu::start() 
{
    sel_last_iteration = {0, false};
    menu_sim_last_iteration = {0, 0};
}


