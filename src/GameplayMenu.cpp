#include "Menus/GameplayMenu.h"
#include "Entity.h"
#include "Components/AllComponents.h"
#include "Scripts/AllScripts.h"
#include "Random.h"
#include "EventQueue.h"

// Constructors / Deconstructor

GameplayMenu::GameplayMenu(InputHandler* _input_handler)
{
    name = "GameplayMenu";

    input_handler = _input_handler;

    tilemap = new Tilemap(30, 30);

    TilemapHandler::active_tilemap = tilemap;

    tilemap_window = new TilemapWindow(MenuManager::texture_handler, tilemap, 0, 0, 
        MenuManager::screen_width / 2, MenuManager::screen_height);
    
    tile_display_window = new BaseWindow(MenuManager::texture_handler, 
        (MenuManager::screen_width / 2), 0, MenuManager::screen_width, 
        MenuManager::screen_height, false);

    windows.push_back(tilemap_window);
    windows.push_back(tile_display_window);

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
    // tilemap->fill_tilemap(grass);

    int x = 1;
    int y = 0;

    while(y < tilemap->get_height())
    {

        while(x < tilemap->get_width())
        {
            int ran_num = Random::get_random_num(0, 1);
            char grass_display = ' ';

            if(ran_num)
            {
                grass_display = '.';
            }

            else
            {
                grass_display = ',';
            }

            Entity* new_grass = new Entity("Grass");
            new_grass->add_component<TransformComponent>(0, 0);
            new_grass->add_component<SpriteComponent>(grass_display, "GREEN", 
                1);
            tilemap->add_entity(new_grass, x, y);
            x++;
        }

        x = 0;
        y++;
    }

    // Player

    player = create_entity(0, 0, 20, 'P', "Player", "BLUE", true);
    player->add_component<StorageComponent>(30);
    player->add_script<HarvestPlant>(
        player->get_component<StorageComponent>());
    player->add_script<PlayerController>(input_handler);
    player->add_script<CameraTrack>(tilemap_window->get_camera());
    tilemap->add_entity(player, 3, 3);

    // Tile Reader

    Entity* tile_reader = create_entity(0, 0, -1, '%', "Tile Reader", 
        "WHITE", false);
    tile_reader->add_script<DisplayEntitiesOnTile>(player, 
        &tile_display_window->text_to_render);
    tilemap->add_entity(tile_reader, 0, 0);

    // Oak Tree
    Entity* oak_tree = create_entity(0, 0, 10, 'T', "Oak Tree", "TAN",
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

    x = 7; 
    y = 6;

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


};

GameplayMenu::~GameplayMenu()
{
    delete tilemap;
    delete tile_display_window;
    delete tilemap_window;
}

// Public members

void GameplayMenu::update()
{
    tilemap_window->update();

    for(Key* k : input_handler->get_active_keys())
    {
        switch(k->id)
        {
            case SDLK_ESCAPE:

                EventQueue::place_event("QUIT");
                input_handler->set_delay(k->id, -1);
                break;

            case SDLK_i:

                MenuManager::activate_menu("InventoryMenu");
                input_handler->set_delay(k->id, -1);
                break;
        }
    }
}

void GameplayMenu::render()
{
    tilemap_window->render();

    tile_display_window->clear_content();
    tile_display_window->render();
}


// Private members

Entity* GameplayMenu::get_player() { return player; }

Entity* GameplayMenu::create_entity(int x_pos, int y_pos, int rendering_priority, 
    char symbol, std::string name, std::string color, bool add_collider)
{
    Entity* new_entity = new Entity(name);
    new_entity->add_component<TransformComponent>(x_pos, y_pos);
    new_entity->add_component<SpriteComponent>(symbol, color, 
        rendering_priority);

    if(add_collider)
    {
        new_entity->add_component<ColliderComponent>();
    }

    return new_entity;
}