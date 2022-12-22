#include "Windows/TilemapWindow.h"
#include "Components/TransformComponent.h"
#include "Components/SPriteComponent.h"


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
    camera_radius = 10;
    camera = new Entity("Camera");
    camera->add_component<TransformComponent>(0, 0);
    camera->add_component<SpriteComponent>('%', "WHITE", -1);
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
    clear_content();

    draw_border();

    TransformComponent* t_comp = camera->get_component<
        TransformComponent>();

    int tilemap_width = tilemap->get_width() - 1;
    int tilemap_height = tilemap->get_height() - 1;

    int start_x = t_comp->x_pos - camera_radius; 
    int start_y = t_comp->y_pos - camera_radius;
    int end_x = t_comp->x_pos + camera_radius;
    int end_y = t_comp->y_pos + camera_radius;

    bool modified_start_x = false;
    bool modified_start_y = false;

    if(start_x < 0) 
    {
        modified_start_x = true;

        start_x = 0;
        
        end_x += (camera_radius - t_comp->x_pos);
    }

    if(end_x > tilemap_width)
    {
        if(!modified_start_x)
        {
            start_x -= end_x - tilemap_width;
        }

        end_x = tilemap_width;
    }

    if(start_y < 0) 
    {
        modified_start_y= true;

        start_y = 0;
        
        end_y += (camera_radius - t_comp->y_pos);
    }

    if(end_y > tilemap_height)
    {

        if(!modified_start_y)
        {
            start_y -= end_y - tilemap_height;
        }

        end_y = tilemap_height;
    }

    for(DisplayCharacter c : tilemap->get_display(start_x, start_y, 
        end_x, end_y))
    {
        add_ch(int(c.symbol), c.color);
        
        if(c.symbol != '\n') add_ch(' ');
    }

    text_handler->draw();
}

bool TilemapWindow::is_position_within_render_bounds(int x, int y)
{
    TransformComponent* t_comp = camera->get_component<
        TransformComponent>();

    int tilemap_width = tilemap->get_width() - 1;
    int tilemap_height = tilemap->get_height() - 1;

    int start_x = t_comp->x_pos - camera_radius; 
    int start_y = t_comp->y_pos - camera_radius;
    int end_x = t_comp->x_pos + camera_radius;
    int end_y = t_comp->y_pos + camera_radius;

    bool modified_start_x = false;
    bool modified_start_y = false;

    if(start_x < 0) 
    {
        modified_start_x = true;

        start_x = 0;
        
        end_x += (camera_radius - t_comp->x_pos);
    }

    if(end_x > tilemap_width)
    {
        if(!modified_start_x)
        {
            start_x -= end_x - tilemap_width;
        }

        end_x = tilemap_width;
    }

    if(start_y < 0) 
    {
        modified_start_y= true;

        start_y = 0;
        
        end_y += (camera_radius - t_comp->y_pos);
    }

    if(end_y > tilemap_height)
    {

        if(!modified_start_y)
        {
            start_y -= end_y - tilemap_height;
        }

        end_y = tilemap_height;
    }

    if(x < start_x || x > end_x || y < start_y || y > end_y) { return false; }

    return true;

}

Entity* TilemapWindow::get_camera() { return camera; }

Tilemap* TilemapWindow::get_tilemap() { return tilemap; }
