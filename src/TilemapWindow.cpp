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
    camera_radius = 7;
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

    int start_x = t_comp->x_pos - camera_radius; 
    int start_y = t_comp->y_pos - camera_radius;
    int end_x = t_comp->x_pos + camera_radius;
    int end_y = t_comp->y_pos + camera_radius;


    for(DisplayCharacter c : tilemap->get_display(start_x, start_y, 
        end_x, end_y))
    {
        add_ch(int(c.symbol), c.color);
        
        if(c.symbol != '\n') add_ch(' ');
        
    }

    text_handler->draw();
}

Entity* TilemapWindow::get_camera() { return camera; }

