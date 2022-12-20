#include "Menus/GameplayMenu.h"
#include "Scripts/CameraTrack.h"
#include "Scripts/PlayerController.h"

// Constructors / Deconstructor

GameplayMenu::GameplayMenu(MenuHandler* _menu_handler, 
    InputHandler* _input_handler, TextureHandler* texture_handler, 
    Tilemap* _tilemap, int start_x, int start_y, int end_x, int end_y) :
    Menu(_menu_handler, _input_handler)
{
    tilemap = _tilemap;
    tilemap_window = new TilemapWindow(texture_handler, tilemap, 
        start_x, start_y, end_x, end_y);

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
                break;
        }
    }
}

void GameplayMenu::render()
{
    tilemap_window->render();
}

void GameplayMenu::start() {}

void GameplayMenu::init_tilemap()
{
    Entity* dirt = create_generic_entity("Dirt", 0, 0, '.', "BROWN", 0, false);
    Entity* player = create_generic_entity("Player", 0, 0, 'P', "BLUE", 
        20, true);
    player->add_script<PlayerController>(input_handler);
    player->add_script<CameraTrack>(tilemap_window->get_camera());

    tilemap->fill_tilemap(dirt);
    // tilemap->fill_tilemap(grass);

    for(int y = 0; y < tilemap->get_height(); y++)
    {
        for(int x = 0; x < tilemap->get_width(); x++)
        {
            int ran_num = Random::get_random_num(0, 2);

            char symbol = '~';

            if(ran_num == 1)
            {
                symbol = '\"';
            }

            else if(ran_num == 2)
            {
                symbol = '\'';
            }

            Entity* grass = create_generic_entity("Grass", 0, 0,
                symbol, "GREEN", 1, false);
            tilemap->add_entity(grass, x, y);
        }
    }

    tilemap->add_entity(player, 5, 5);
}
