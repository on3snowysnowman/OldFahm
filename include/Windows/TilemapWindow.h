#pragma once

#include "BaseWindow.h"
#include "../Tilemap.h"

class TilemapWindow : public BaseWindow
{

public:

    TilemapWindow();
    TilemapWindow(TextureHandler* _texture_handler, 
        Tilemap* _tilemap, int _start_x, int _start_y, int _end_x, int _end_y);
    ~TilemapWindow();

    void update() override;
    void render() override;

private:

    Tilemap* tilemap;

};
