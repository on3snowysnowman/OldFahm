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

    Uint64 init = SDL_GetTicks64();

    tilemap = new Tilemap(1000, 1000);

    tilemap_window = new TilemapWindow(texture_handler, tilemap, 0, 0, 
        screen_width, screen_height);

    Entity* dirt = new Entity("Dirt");
    dirt->add_component(new TransformComponent(0, 0));
    dirt->add_component(new SpriteComponent('~', "BROWN", 0));
    tilemap->add_entity(dirt, 0, 0);
    tilemap->fill_tilemap(dirt);

    Entity* grass = new Entity("Grass");
    grass->add_component(new TransformComponent(0, 0));
    grass->add_component(new SpriteComponent('\'', "GREEN", 1));
    tilemap->add_entity(grass, 0, 0);
    tilemap->fill_tilemap(grass);

    int elapsed = SDL_GetTicks64() - init;

    std::cout << "Elapsed: " << elapsed;
    exit(0);

    // Entity* player = new Entity("Player");
    // player->add_component(new TransformComponent(0, 0));
    // player->add_component(new SpriteComponent('P', "BLUE", 20));
    // player->add_component(new ColliderComponent());
    // player->add_script(new PlayerController(input_handler));
    // tilemap->add_entity(player, 3, 3);

    startup_screen();
    start_OJAE(); 
}


// Private Members

void Fahm::startup_screen() {}

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
        }
    }
}

void Fahm::update() 
{
    handle_queue_events();

    tilemap_window->update();
}

void Fahm::render()
{
    clear_screen();

    tilemap_window->render();

    draw_to_screen();
}
