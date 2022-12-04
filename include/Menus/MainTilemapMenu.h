#pragma once

#include "Menu.h"
#include "../Windows/BaseWindow.h"
#include "../Windows/TilemapWindow.h"

class MainTilemapMenu : public Menu
{

public:

    MainTilemapMenu(TextureHandler* texture_handler);

    void update() override;

    void render() override;

private: 

      

};
