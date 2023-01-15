#include "Windows/TilemapWindow.h"
#include "Components/TransformComponent.h"
#include "Components/SPriteComponent.h"
#include "TileID.h"


// Constructors / Deconstructor

TilemapWindow::TilemapWindow()
{
    tilemap = nullptr;
    camera = nullptr;
    camera_radius = 0;

    Debug::log("[WARN] TilemapWindow.TilemapWindow -> Called by default"
    " constructor, initialized null pointer for tilemap pointer");
}

TilemapWindow::TilemapWindow(TextureHandler* _texture_handler, 
    Tilemap* _tilemap, int _start_x, int _start_y, int _end_x, int _end_y) : 
    BaseWindow(_texture_handler, _start_x, _start_y, _end_x, _end_y, false)
{
    tilemap = _tilemap;
    tilemap_renderer = new TilemapRenderer(_texture_handler);
    camera_radius = 10;
    camera = new Entity("Camera");
    camera->add_component<TransformComponent>(0, 0);
    camera->add_component<SpriteComponent>();
    tilemap->add_entity(camera, 0, 0);
}

TilemapWindow::~TilemapWindow() {}


// Public Members 

void TilemapWindow::update()
{
    tilemap->update();
}

void TilemapWindow::render()
{
    // clear_content();

    tilemap_renderer->clear();

    draw_border();

    TransformComponent* t_comp = camera->get_component<
        TransformComponent>();

    int tilemap_width = tilemap->get_width() - 1;
    int tilemap_height = tilemap->get_height() - 1;

    int camera_start_x = t_comp->x_pos - camera_radius; 
    int camera_start_y = t_comp->y_pos - camera_radius;
    int camera_end_x = t_comp->x_pos + camera_radius;
    int camera_end_y = t_comp->y_pos + camera_radius;

    bool modified_start_x = false;
    bool modified_start_y = false;

    if(camera_start_x < 0) 
    {
        modified_start_x = true;

        camera_start_x = 0;
        
        camera_end_x += (camera_radius - t_comp->x_pos);
    }

    if(camera_end_x > tilemap_width)
    {
        if(!modified_start_x)
        {
            camera_start_x -= camera_end_x - tilemap_width;
        }

        camera_end_x = tilemap_width;
    }

    if(camera_start_y < 0) 
    {
        modified_start_y= true;

        camera_start_y = 0;
        
        camera_end_y += (camera_radius - t_comp->y_pos);
    }

    if(camera_end_y > tilemap_height)
    {

        if(!modified_start_y)
        {
            camera_start_y -= camera_end_y - tilemap_height;
        }

        camera_end_y = tilemap_height;
    }

    int tile_size = tilemap_renderer->get_tile_size();

    int cursor_x = start_x;
    int cursor_y = start_y;

    for(int y = camera_start_y; y < camera_end_y; y++)
    {
        for(int x = camera_start_x; x < camera_end_x; x++)
        {
            for(Entity* e : tilemap->get_entity_handler()->
                get_entities_at_position(x, y))
            {
                SpriteComponent* e_s_comp = e->get_component<SpriteComponent>();

                if(e_s_comp->priority < 0) continue;

                TileID e_tile_id = e_s_comp->tile_id;
                tilemap_renderer->add(cursor_x, cursor_y, e_tile_id);
            }

            cursor_x += tile_size;
        }

        cursor_x = start_x;
        cursor_y += tile_size;
    }


    // for(TileID tile_id : tilemap->get_display(camera_start_x, camera_start_y, 
    //     camera_end_x, camera_end_y))
    // {
    //     tilemap_renderer->add(cursor_x, cursor_y, tile_id);

    //     current_tiles_per_row_count++;

    //     if(current_tiles_per_row_count == num_tiles_per_row + 1)
    //     {
    //         current_tiles_per_row_count = 1;

    //         cursor_x = start_x;
    //         cursor_y += tile_size;
    //         continue;
    //     }

    //     cursor_x += tile_size;       
    // }

    // for(std::vector<TileID> vector_of_ids : tilemap->get_display(start_x, start_y, 
    //     end_x, end_y))
    // {
    //     // add_ch(int(c.tile_id), c.color);
        
    //     // if(c.tile_id != '\n') add_ch(' ');

        
    // }

    // text_handler->draw();

    tilemap_renderer->draw();
}

bool TilemapWindow::is_position_within_render_bounds(int x, int y)
{
    TransformComponent* t_comp = camera->get_component<
        TransformComponent>();

        int tilemap_width = tilemap->get_width() - 1;
    int tilemap_height = tilemap->get_height() - 1;

    int camera_start_x = t_comp->x_pos - camera_radius; 
    int camera_start_y = t_comp->y_pos - camera_radius;
    int camera_end_x = t_comp->x_pos + camera_radius;
    int camera_end_y = t_comp->y_pos + camera_radius;

    bool modified_start_x = false;
    bool modified_start_y = false;

    if(camera_start_x < 0) 
    {
        modified_start_x = true;

        camera_start_x = 0;
        
        camera_end_x += (camera_radius - t_comp->x_pos);
    }

    if(camera_end_x > tilemap_width)
    {
        if(!modified_start_x)
        {
            camera_start_x -= camera_end_x - tilemap_width;
        }

        camera_end_x = tilemap_width;
    }

    if(camera_start_y < 0) 
    {
        modified_start_y= true;

        camera_start_y = 0;
        
        camera_end_y += (camera_radius - t_comp->y_pos);
    }

    if(camera_end_y > tilemap_height)
    {

        if(!modified_start_y)
        {
            camera_start_y -= camera_end_y - tilemap_height;
        }

        camera_end_y = tilemap_height;
    }


    if(x < camera_start_x || x > camera_end_x || 
        y < camera_start_y || y > camera_end_y) { return false; }

    return true;

}

Entity* TilemapWindow::get_camera() { return camera; }

Tilemap* TilemapWindow::get_tilemap() { return tilemap; }
