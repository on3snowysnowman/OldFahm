#pragma once

#include "Menu.h"
#include "../InputHandler.h"
#include "../Windows/BaseWindow.h"

class InventoryMenu : public Menu
{

public:

    InventoryMenu(InputHandler* _input_handler);
    ~InventoryMenu();

    void update() override;
    void render() override;

private:

    InputHandler* input_handler;
    BaseWindow* full_window;
};
