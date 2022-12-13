#include "Menus/Menu.h"
#include "Debug.h"

#include <iostream>
//____________________________MenuManager______________________________________

int MenuManager::screen_width = 0;
int MenuManager::screen_height = 0;

TextureHandler* MenuManager::texture_handler = nullptr;
std::vector<Menu*> MenuManager::active_menus;
std::vector<Menu*> MenuManager::all_menus;

// Public members

void MenuManager::add_menu(Menu* _menu)
{
    all_menus.push_back(_menu);
}

void MenuManager::activate_menu(std::string _menu_name)
{

    for(Menu* m : all_menus)
    {
        if(m->get_name() == _menu_name)
        {
            active_menus.push_back(m);
            return;
        }
    }

    std::string message = "[WARN] MenuManager.set_active_menu(MenuType _menu"
        "_type) where _menu_type is \"" + _menu_name + "\""
        " -> Could not find a menu matching _menu_type in menu list";

    Debug::log(message);
}

void MenuManager::activate_menu(Menu* _menu)
{
    active_menus.push_back(_menu);
}

void MenuManager::deactivate_menu(Menu* _menu)
{
    for(int i = active_menus.size() - 1; i >= 0; i--)
    {
        if(active_menus.at(i) == _menu)
        {
            active_menus.erase(active_menus.begin() + i);
            return;
        }
    }

    std::string message = "[WARN] MenuManager.deactivate_menu(Menu* _menu) where "
        " _menu's name is \"" + _menu->get_name() + "\" -> Could not find Menu"
        " in active menus";
    Debug::log(message);
}

void MenuManager::deactivate_menu(std::string _menu_name)
{
    for(int i = active_menus.size() - 1; i--; i >= 0)
    {
        if(active_menus.at(i)->get_name() == _menu_name)
        {
            active_menus.erase(active_menus.begin() + i);
            return;
        }
    }
    
    std::string message = "[WARN] MenuManager.deactivate_menu(std::string"
        "_menu_name) where  _menu's name is \"" + _menu_name + "\" -> "
        "Could not find Menu in active menus";
    Debug::log(message);
}

bool MenuManager::has_active_menu()
{
    return active_menus.size() > 0;
}

Menu* MenuManager::get_active_menu()
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
    MenuManager::add_menu(this);
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
