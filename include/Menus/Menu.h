#pragma once

#include <vector>
#include <list>

#include "InputHandler.h"

enum MenuID
{
    BASE,
    GAMEPLAY,
    PAUSE,
    INVENTORY
};

class MenuHandler;

class Menu
{

public:

    Menu();
    Menu(MenuHandler* _menu_handler, InputHandler* _input_handler);

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void start() = 0;

    MenuID get_menu_id();

protected:

    MenuHandler* menu_handler;
    InputHandler* input_handler;

    MenuID menu_id = BASE;

};

class MenuHandler
{

public:

    MenuHandler();
    
    void update();
    void render();

    void add_menu(Menu* menu);
    void deactivate_active_menu();

    bool activate_menu(Menu* menu);
    bool activate_menu(MenuID menu_id);

private:

    std::vector<Menu*> all_menus;
    std::list<Menu*> active_menus;
};

