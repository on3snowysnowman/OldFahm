#pragma once

#include "Menu.h"
#include "../InputHandler.h"
#include "../TextureHandler.h"
#include "../MenuTools.h"
#include "../Windows/BaseWindow.h"

class PauseMenu : public Menu
{

public:

    PauseMenu(MenuHandler* _menu_handler, InputHandler* _input_handler,
        TextureHandler* texture_handler, 
        int start_x, int start_y, int end_x, int end_y);

    void update() override;
    void render() override;
    void start() override;

private:


    std::pair<int, int> sel_last_iteration {0, false};
    std::pair<int,int> menu_sim_last_iteration {0, 0};

    std::string cursor_color;

    MenuTools* menu_tools;

    BaseWindow* full_window;

};
