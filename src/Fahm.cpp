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

    full_window = new BaseWindow(texture_handler, 0, 0, screen_width,
        screen_height, false);

    menu_handler = new MenuHandler();

    tilemap = new Tilemap(45, 45);

    gameplay_menu = new GameplayMenu(menu_handler, input_handler, 
        texture_handler, tilemap, 0, 0, screen_width, screen_height);

    pause_menu = new PauseMenu(menu_handler, input_handler, texture_handler, 
        0, 0, screen_width, screen_height);

    menu_handler->activate_menu(gameplay_menu);

    loading_screen();

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
            // case SDLK_ESCAPE:   

            //     running = false;
            //     break;

            case SDLK_RIGHTBRACKET:

                input_handler->set_delay(k->id);
                break;

            case SDLK_LEFTBRACKET:

                input_handler->set_delay(k->id);
                break;
        }
    }
}

void Fahm::update() 
{
    handle_key_press();
    handle_queue_events();

    menu_handler->update();
}

void Fahm::render()
{
    clear_screen();

    menu_handler->render();

    draw_to_screen();
}
