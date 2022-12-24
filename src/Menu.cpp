#include <iostream>

#include "Menus/Menu.h"
#include "Debug.h"

//______________________________MENU___________________________________________


// Constructors / Deconstructors

Menu::Menu() {}

Menu::Menu(MenuHandler* _menu_handler, InputHandler* _input_handler,
    TextureHandler* _texture_handler)
{
    menu_handler = _menu_handler;
    input_handler = _input_handler;
    texture_handler = _texture_handler;

    menu_handler->add_menu(this);
}


// Public Members

void Menu::update() {}

void Menu::render() {}

void Menu::start() {}

MenuID Menu::get_menu_id()
{
    return menu_id;
}


//____________________________MENUHANDLER______________________________________


// Constructors / Deconstructor

MenuHandler::MenuHandler() {}


// Public Members


void MenuHandler::update()
{
    if(active_menus.size() > 0)
    {
        active_menus.back()->update();
    }
}

void MenuHandler::render()
{
    if(active_menus.size() > 0)
    {
        active_menus.back()->render();
    }
}

void MenuHandler::add_menu(Menu* menu)
{
    all_menus.push_back(menu);
}

void MenuHandler::deactivate_active_menu()
{
    if(active_menus.size() > 0)
    {
        active_menus.pop_back();
    }
}

bool MenuHandler::activate_menu(Menu* menu)
{
    active_menus.push_back(menu);
    menu->start();
    return true;
}

bool MenuHandler::activate_menu(MenuID menu_id)
{

    for(Menu* m : all_menus)
    {
        if(m->get_menu_id() == menu_id)
        {
            active_menus.push_back(m);
            m->start();
            return true;
        }
    }
    
    std::string message = "[WAR] MenuHandler.activate_menu(MenuID menu_id) "
        "where \"menu_id\" is " + std::to_string(menu_id) + " -> Failed to find menu of "
        "specified type";

    Debug::log(message);

    return false;
}

Menu* MenuHandler::get_menu(MenuID menu_id)
{
    for(Menu* m : all_menus)
    {
        if(m->get_menu_id() == menu_id)
        {
            return m;
        }
    }

    std::string message = "[WAR] MenuHandler.get_menu(MenuID menu_id) where "
        "menu_id = " + std::to_string(menu_id) + " -> Failed to find menu of "
        "specified type";

    Debug::log(message);
}
