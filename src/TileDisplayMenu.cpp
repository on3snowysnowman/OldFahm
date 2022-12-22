#include "Menus/TileDisplayMenu.h"
#include "Menus/GameplayMenu.h"
#include "Components/TransformComponent.h"
#include "Scripts/CursorController.h"


// Constructors / Deconstructor

TileDisplayMenu::TileDisplayMenu(MenuHandler* _menu_handler, 
    InputHandler* _input_handler, TextureHandler* _texture_handler, 
    int start_x, int start_y, int end_x, int end_y) : 
    Menu(_menu_handler, _input_handler, _texture_handler)
{
    GameplayMenu* gameplay_menu = static_cast<GameplayMenu*>(
        menu_handler->get_menu(GAMEPLAY));

    tilemap_window = gameplay_menu->get_tilemap_window();
    tile_display_window = new BaseWindow(texture_handler, 
        int((end_x - start_x) / 2), start_y, end_x, end_y, false);
        
    tilemap = tilemap_window->get_tilemap();

    cursor = create_generic_entity("Cursor", 0, 0, 'X', "WHITE", 21,
        false);
    cursor->add_script<CursorController>(input_handler, tilemap_window);

    menu_id = CURSOR;
}


// Public Members

void TileDisplayMenu::update()
{
    for(Script* s : cursor->scripts)
    {
        s->update();
    }

    tile_display_window->clear_content();

    TransformComponent* cursor_t_comp = cursor->
        get_component<TransformComponent>();

    for(Entity* e : tilemap->get_entities_at_position(
        cursor_t_comp->x_pos, cursor_t_comp->y_pos))
    {
        if(e->name == cursor->name) continue;

        SpriteComponent* targ_e_s_comp = e->get_component<SpriteComponent>();

        if(targ_e_s_comp->priority < 0) continue;

        tile_display_window->add_ch(targ_e_s_comp->symbol, 
            targ_e_s_comp->color);
        tile_display_window->add_str(" : ");
        tile_display_window->add_str(e->name);
        tile_display_window->add_new_line();
    }

    std::vector<Key*> active_keys = input_handler->get_active_keys();

    if(active_keys.size() == 0) return;

    switch(active_keys.at(0)->id)
    {
        case SDLK_f:
            tilemap->remove_entity(cursor);
            menu_handler->deactivate_active_menu();
            input_handler->set_delay(SDLK_f, -1);
            break;

        case SDLK_ESCAPE:

            menu_handler->activate_menu(PAUSE);
            input_handler->set_delay(SDLK_ESCAPE, -1);
            break;
    }
}

void TileDisplayMenu::render()
{
    tilemap_window->render();
    tile_display_window->render();
}

void TileDisplayMenu::start() 
{   
    TransformComponent* camera_t_comp = tilemap_window->get_camera()->
        get_component<TransformComponent>();

    tilemap->add_entity(cursor, camera_t_comp->x_pos, camera_t_comp->y_pos);
}
