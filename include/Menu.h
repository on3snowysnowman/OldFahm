#pragma once

#include <vector>
#include <list>

enum MenuID
{
    GAMEPLAY,
    INVENTORY
};

class Menu;

class MenuHandler
{

public:

    MenuHandler() {}
    
    void add_menu(Menu* menu) 
    {
        all_menus.push_back(menu);
    }

    void activate_menu(Menu* menu) 
    {
        active_menus.push_back(menu);
    }

    void activate_menu(MenuID menu_id) 
    {
        
    }

    void deactivate_active_menu()
    {
        
    }

private:

    std::vector<Menu*> all_menus;
    std::list<Menu*> active_menus;
};
1
