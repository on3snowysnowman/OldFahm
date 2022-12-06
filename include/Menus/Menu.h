#pragma once

#include <vector>
#include <string>

#include "../TextureHandler.h"
#include "../Windows/BaseWindow.h"

class Menu;

struct MenuData
{
    static int screen_width;
    static int screen_height;

    static TextureHandler* texture_handler;
    
    static std::vector<Menu*> active_menus;
    static std::vector<Menu*> all_menus;

    static void add_menu(Menu* _menu);
    static void activate_menu(Menu* _menu);
    static void activate_menu(std::string _menu_name);
    static void deactivate_menu(Menu* _menu);
    static void deactivate_menu(std::string _menu_name);

    static bool has_active_menu();

    static Menu* get_active_menu();

};


class Menu
{

public:

    Menu();

    virtual void update();
    virtual void render();
    void zoom_in();
    void zoom_out();

    std::string get_name();

protected:

    std::string name;

    std::vector<BaseWindow*> windows;
};
