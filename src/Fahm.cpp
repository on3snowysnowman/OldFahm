#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Fahm.h"
#include "Components/AllComponents.h"
#include "Scripts/AllScripts.h"
#include "EventQueue.h"
#include "Random.h"
#include "CollisionHandler.h"
#include "Menus/AllMenus.h"


// Constructors / Deconstructor
 
Fahm::Fahm(const char* title) : 
    ojae::OJAsciiEngine::OJAsciiEngine(title) {}

Fahm::~Fahm() {}


// Public Members

void Fahm::start()
{
    MenuManager::screen_width = screen_width;
    MenuManager::screen_height = screen_height;

    MenuManager::texture_handler = texture_handler;

    full_window = new BaseWindow(texture_handler, 0, 0, screen_width,
        screen_height, false);

    loading_screen();

    GameplayMenu* gameplay_menu = new GameplayMenu(input_handler);
    InventoryMenu* inventory_menu = new InventoryMenu(input_handler, 
        gameplay_menu->get_player()->get_component<StorageComponent>());

    MenuManager::activate_menu(gameplay_menu);

    startup_screen();
    start_OJAE(); 
}


// Private Members

void Fahm::startup_screen() 
{
    full_window->add_str("Fahm - VERSION .1\n");
    full_window->add_str("Press Escape to Continue...");

    full_window->render();

    std::vector<Key*> pressed_keys = input_handler->get_active_keys();

    for(Key* k : pressed_keys)
    {
        if(k->id == SDLK_ESCAPE)
        {
            return;
        }
    }

    SDL_Delay(16.67);
}

void Fahm::loading_screen() 
{
    clear_screen();

    full_window->add_str("Loading...");
    full_window->render();

    draw_to_screen();
}

void Fahm::handle_queue_events()
{
    while(EventQueue::has_events())
    {
        std::string targ_event = EventQueue::pull_event();

        if(targ_event == "QUIT")
        {
            running = false;
        }
    }
}

void Fahm::handle_key_press()
{
    std::vector<Key*> keys_pressed = input_handler->get_active_keys();

    for(Key* k : keys_pressed)
    {
        switch(k->id)
        {

            case SDLK_RIGHTBRACKET:

                if(MenuManager::active_menus.size() > 0)
                {
                    MenuManager::get_active_menu()->zoom_in();
                    MenuManager::get_active_menu()->zoom_in();
                }

                input_handler->set_delay(k->id);
                break;

            case SDLK_LEFTBRACKET:

                if(MenuManager::active_menus.size() > 0)
                {
                    MenuManager::get_active_menu()->zoom_out();
                    MenuManager::get_active_menu()->zoom_out();
                }
                input_handler->set_delay(k->id);
                break;
        }
    }
}

void Fahm::update() 
{
    handle_key_press();
    handle_queue_events();

    if(MenuManager::has_active_menu())
    {
        MenuManager::get_active_menu()->update();
    }
}

void Fahm::render()
{
    clear_screen();

    if(MenuManager::has_active_menu())
    {
        MenuManager::get_active_menu()->render();
    }

    draw_to_screen();
}
