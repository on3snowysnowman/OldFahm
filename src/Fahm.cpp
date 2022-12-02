#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Fahm.h"
#include "Components/AllComponents.h"
#include "Scripts/AllScripts.h"
#include "EventQueue.h"
#include "Random.h"
#include "CollisionHandler.h"


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

    tilemap = new Tilemap(30, 30);

    tilemap_window = new TilemapWindow(texture_handler, tilemap, 0, 0, 
        screen_width / 2, screen_height);
    
    inventory_window = new BaseWindow(texture_handler, (screen_width / 2),
        0, screen_width, (screen_height * .75), false);
    text_window = new BaseWindow(texture_handler, (screen_width / 2),
        (screen_height * .75), screen_width, screen_height, false);

    // Dirt

    Entity* dirt = new Entity("Dirt");
    dirt->add_component<TransformComponent>(0, 0);
    dirt->add_component<SpriteComponent>('~', "BROWN", 0);
    tilemap->add_entity(dirt, 0, 0);
    tilemap->fill_tilemap(dirt);

    // Grass

    Entity* grass = new Entity("Grass");
    grass->add_component<TransformComponent>(0, 0);
    grass->add_component<SpriteComponent>('~', "GREEN", 1);
    tilemap->add_entity(grass, 0, 0);
    tilemap->fill_tilemap(grass);

    // Player

    Entity* player = create_entity(0, 0, 20, 'P', "Player", "BLUE", true);
    player->add_component<StorageComponent>(30);
    player->add_script<HarvestPlant>(
        player->get_component<StorageComponent>());
    player->add_script<PlayerController>(input_handler);
    player->add_script<CameraTrack>(tilemap_window->get_camera());
    player->add_script<DisplayStorage>(&inventory_window->text_to_render,
        player->get_component<StorageComponent>());
    tilemap->add_entity(player, 3, 3);

    // Tile Reader

    Entity* tile_reader = create_entity(0, 0, -1, '%', "Tile Reader", 
        "WHITE", false);
    tile_reader->add_script<DisplayEntitiesOnTile>(player, 
        &text_window->text_to_render);
    tilemap->add_entity(tile_reader, 0, 0);

    // Oak Tree
    Entity* oak_tree = create_entity(0, 0, 10, 'T', "Oak Tree", "BROWN",
        true);
    oak_tree->entity_handler = tilemap->get_entity_handler();

    int i = 0;

    while(i < tilemap->get_width())
    {
        int x_pos = Random::get_random_num(0, tilemap->get_width());
        int y_pos = Random::get_random_num(0, tilemap->get_height());

        if(CollisionHandler::is_traversable(oak_tree, x_pos, y_pos))
        {
            tilemap->add_entity(oak_tree, x_pos, y_pos);
            break;
        }

        i++;
    }

    int iterations = 0;

    int tilemap_size = pow(tilemap->get_width(), 2);
    int bound = tilemap_size * 0.05;
    
    for(int i = 0; i < bound; i++)
    {
        if(iterations >= tilemap_size)
        {
            break;
        }

        int x_pos = Random::get_random_num(0, tilemap->get_width());
        int y_pos = Random::get_random_num(0, tilemap->get_height());

        if(!CollisionHandler::is_traversable(oak_tree, x_pos, y_pos))
        {
            i--;
            iterations++;
            continue;
        }

        iterations++;
        tilemap->add_copy_entity(oak_tree, x_pos, y_pos);
    }

    // Wheat

    Entity* wheat = create_entity(6, 6, 3, 'W', "Wheat", "YELLOW", false);
    wheat->add_tag("HARVESTABLE");
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

    inventory_window->clear_content();
    inventory_window->render();

    tilemap_window->render();

    draw_to_screen();
}
