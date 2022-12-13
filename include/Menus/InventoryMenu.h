#pragma once

#include "Menu.h"
#include "../InputHandler.h"
#include "../Windows/BaseWindow.h"
#include "../Components/StorageComponent.h"

class InventoryMenu : public Menu
{

public:

    InventoryMenu(InputHandler* _input_handler, StorageComponent*
        _player_storage_component);
    ~InventoryMenu();

    void update() override;
    void render() override;

private:

    InputHandler* input_handler;
    BaseWindow* full_window;

    StorageComponent* player_storage_component;
};
