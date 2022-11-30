#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Fahm.h"
#include "Components/AllComponents.h"
#include "Scripts/AllScripts.h"
#include "EventQueue.h"


// Constructors / Deconstructor

Fahm::Fahm(const char* title) : 
    ojae::OJAsciiEngine::OJAsciiEngine(title) {}

Fahm::~Fahm() {}


// Public Members

void Fahm::start()
{
    full_window = new BaseWindow(texture_handler, 0, 0, screen_width, 
        screen_height, false);

    loading_screen();

    tilemap = new Tilemap(15, 15);

    tilemap_window = new TilemapWindow(texture_handler, tilemap, 0, 0, 
        screen_width / 2, screen_height);
    
    text_window = new BaseWindow(texture_handler, (screen_width / 2) + 1,
        0, screen_width, screen_height, false);

    Entity* dirt = new Entity("Dirt");
    dirt->add_component<TransformComponent>(0, 0);
    dirt->add_component<SpriteComponent>('~', "BROWN", 0);
    tilemap->add_entity(dirt, 0, 0);
    tilemap->fill_tilemap(dirt);

    Entity* grass = new Entity("Grass");
    grass->add_component<TransformComponent>(0, 0);
    grass->add_component<SpriteComponent>('\'', "GREEN", 1);
    tilemap->add_entity(grass, 0, 0);
    tilemap->fill_tilemap(grass);

    Entity* player = new Entity("Player");
    player->add_component<TransformComponent>(0, 0);
    player->add_component<SpriteComponent>('P', "BLUE", 20);
    player->add_component<ColliderComponent>();
    player->add_script(new PlayerController(input_handler));
    player->add_script(new CameraTrack(tilemap_window->get_camera()));
    tilemap->add_entity(player, 3, 3);

    Entity* tile_reader = create_entity(0, 0, -1, '%', "Tile Reader", 
        "WHITE", false);
    tile_reader->add_script(new DisplayEntitiesOnTile(player, 
        &text_window->text_to_render));
    tilemap->add_entity(tile_reader, 0, 0);

    Entity* wheat = create_entity(6, 6, 3, 'W', "Wheat", "YELLOW", false);
    tilemap->add_entity(wheat, 6, 6);

    int x = 7; 
    int y = 6;

    while(y != 8)
    {
        while(x != 14)
        {
            tilemap->add_copy_entity(wheat, x, y);
            x++;
        }

        x = 6;
        y++;
    }

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

        std::cout << "Event Processed: " << targ_event << '\n';
    }
}

void Fahm::handle_key_press()
{
    std::vector<Key*> keys_pressed = input_handler->get_active_keys();

    for(Key* k : keys_pressed)
    {
        switch(k->id)
        {
            case SDLK_ESCAPE:
                
                running = false;
                break;

            case SDLK_RIGHTBRACKET:

                tilemap_window->zoom_in();
                text_window->zoom_in();
                input_handler->set_delay(k->id);
                break;

            case SDLK_LEFTBRACKET:

                tilemap_window->zoom_out();
                text_window->zoom_out();
                input_handler->set_delay(k->id);
                break;
        }
    }
}

void Fahm::update() 
{
    handle_key_press();
    // handle_queue_events();

    tilemap_window->update();
}

void Fahm::render()
{
    clear_screen();

    text_window->clear_content();
    text_window->render();
    tilemap_window->render();

    draw_to_screen();
}
