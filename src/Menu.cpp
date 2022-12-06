#include "Menus/Menu.h"
#include "Debug.h"

#include <iostream>
//____________________________MenuData______________________________________

int MenuData::screen_width = 0;
int MenuData::screen_height = 0;

TextureHandler* MenuData::texture_handler = nullptr;
std::vector<Menu*> MenuData::active_menus;
std::vector<Menu*> MenuData::all_menus;

// Public members

void MenuData::add_menu(Menu* _menu)
{
    all_menus.push_back(_menu);
}

void MenuData::activate_menu(std::string _menu_name)
{

    for(Menu* m : all_menus)
    {
        if(m->get_name() == _menu_name)
        {
            active_menus.push_back(m);
            return;
        }
    }

    std::string message = "[WARN] MenuData.set_active_menu(MenuType _menu"
        "_type) where _menu_type is \"" + _menu_name + "\""
        " -> Could not find a menu matching _menu_type in menu list";

    Debug::log(message);
}

void MenuData::activate_menu(Menu* _menu)
{
    active_menus.push_back(_menu);
}

void MenuData::deactivate_menu(Menu* _menu)
{
    for(int i = active_menus.size() - 1; i >= 0; i--)
    {
        if(active_menus.at(i) == _menu)
        {
            active_menus.erase(active_menus.begin() + i);
            return;
        }
    }

    std::string message = "[WARN] MenuData.deactivate_menu(Menu* _menu) where "
        " _menu's name is \"" + _menu->get_name() + "\" -> Could not find Menu"
        " in active menus";
    Debug::log(message);
}

void MenuData::deactivate_menu(std::string _menu_name)
{
    for(int i = active_menus.size() - 1; i--; i >= 0)
    {
        if(active_menus.at(i)->get_name() == _menu_name)
        {
            active_menus.erase(active_menus.begin() + i);
            return;
        }
    }
    
    std::string message = "[WARN] MenuData.deactivate_menu(std::string"
        "_menu_name) where  _menu's name is \"" + _menu_name + "\" -> "
        "Could not find Menu in active menus";
    Debug::log(message);
}

bool MenuData::has_active_menu()
{
    return active_menus.size() > 0;
}

Menu* MenuData::get_active_menu()
{
    if(!has_active_menu)
    {
        return nullptr;
    }

    return active_menus.at(active_menus.size() - 1);
}


// _________________________________MENU__________________________________________

// Constructors / Deconstructor

Menu::Menu() 
{
    MenuData::add_menu(this);
    name = "Menu";
}


// Public members

void Menu::update() {}

void Menu::render() {}

void Menu::zoom_in() 
{
    for(BaseWindow* b : windows)
    {
        b->zoom_in();
    }
}

void Menu::zoom_out() 
{
    for(BaseWindow* b : windows)
    {
        b->zoom_out();
    }
}

std::string Menu::get_name() { return name; }
