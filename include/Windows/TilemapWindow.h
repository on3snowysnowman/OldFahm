#pragma once

#include "BaseWindow.h"
#include "../Tilemap.h"
#include "../Entity.h"

class TilemapWindow : public BaseWindow
{

public:

    TilemapWindow();
    TilemapWindow(TextureHandler* _texture_handler, 
        Tilemap* _tilemap, int _start_x, int _start_y, int _end_x, int _end_y);
    ~TilemapWindow();

    void update() override;
    void render() override;

    bool is_position_within_render_bounds(int x, int y);

    Entity* get_camera();

    Tilemap* get_tilemap();

private:

    int camera_radius;

    Entity* camera;
    Tilemap* tilemap;

};
