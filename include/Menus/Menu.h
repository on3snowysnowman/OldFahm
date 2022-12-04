#pragma once

#include "../TextureHandler.h"

class Menu
{

public:

    Menu();

    Menu(TextureHandler* _texture_handler);

    virtual void update();

    virtual void render();

protected:

    bool active;
    
    TextureHandler* texture_handler;

};
