#include "Menus/GameplayMenu.h"
#include "Scripts/CameraTrack.h"
#include "Scripts/PlayerController.h"
#include "TileID.h"

// Constructors / Deconstructor

GameplayMenu::GameplayMenu(MenuHandler* _menu_handler, 
    InputHandler* _input_handler, TextureHandler* _texture_handler, 
    Tilemap* _tilemap, int start_x, int start_y, int end_x, int end_y) :
    Menu(_menu_handler, _input_handler, _texture_handler)
{
    tilemap = _tilemap;
    tilemap_window = new TilemapWindow(_texture_handler, tilemap, 
        start_x, start_y, int((end_x - start_x) / 2), end_y);

    inventory_window = new BaseWindow(_texture_handler, 
        int((end_x - start_x) / 2), start_y, end_x, end_y, false);

    menu_id = GAMEPLAY;

    init_tilemap();
}


// Public Members

void GameplayMenu::update()
{

    tilemap_window->update();

    for(Key* key : input_handler->get_active_keys())
    {

        switch(key->id)
        {
            case SDLK_ESCAPE:

                menu_handler->activate_menu(PAUSE);
                input_handler->set_delay(SDLK_ESCAPE, -1);
                break;
            
            case SDLK_f:

                menu_handler->activate_menu(CURSOR);
                input_handler->set_delay(SDLK_f, -1);
                break;
        }
    }

    inventory_window->clear_content();

    inventory_window->add_str("Inventory:\n\n");

    for(std::pair<Text, int> _pair : player_inventory->get_storage_display())
    {
        inventory_window->add_str(_pair.first.content, _pair.first.color);
        inventory_window->add_str(" x" + std::to_string(_pair.second));
        inventory_window->add_new_line();
    }
}

void GameplayMenu::render()
{
    tilemap_window->render();
    inventory_window->render();
}

void GameplayMenu::start() {}

void GameplayMenu::init_tilemap()
{
    Entity* dirt = create_generic_entity("Dirt", 0, 0, DIRT, 0, false);

    Entity* grass = create_generic_entity("Grass", 0, 0,
        GRASS, 1, false);

    player = create_generic_entity("Player", 0, 0, PLAYER,
        20, true);
    player->add_component<StorageComponent>();
    player->add_script<PlayerController>(input_handler);
    player->add_script<CameraTrack>(tilemap_window->get_camera());
    player->add_script<HarvestPlant>(player->get_component<
        StorageComponent>());

    player_inventory = player->get_component<StorageComponent>();

    // Entity* oak_tree = create_generic_entity("Oak Tree", 10, 10, 'T', "TAN",
    //     10, true);

    Entity* wheat = create_generic_entity("Wheat", 0, 0, WHEAT, 5, 
        false);
    wheat->add_tag("HARVESTABLE");

    Entity* carrot = create_generic_entity("Carrot", 0, 0, CARROT, 5, 
        false);
    carrot->add_tag("HARVESTABLE");

    tilemap->fill_tilemap(dirt);
    tilemap->fill_tilemap(grass);

    tilemap->add_entity(player, 5, 5);
    // tilemap->add_entity(oak_tree, 10, 10);

    int x = 2; 
    int y = 2;

    tilemap->add_entity(wheat, x, y);

    x++;

    while(y < 4)
    {
        while(x < 12)
        {
            tilemap->add_copy_entity(wheat, x, y);
            x++;
        }

        x = 2;
        y++;
    }

    x = 2;
    y = 4;

    tilemap->add_entity(carrot, x, y);

    x++;

    while(y < 6)
    {
        while(x < 12)
        {
            tilemap->add_copy_entity(carrot, x, y);
            x++;
        }

        x = 2;
        y++;
    }
}

Entity* GameplayMenu::get_player() { return player; }

TilemapWindow* GameplayMenu::get_tilemap_window()
{
    return tilemap_window;
}
