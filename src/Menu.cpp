#include "Menus/Menu.h"
#include "Debug.h"


// Constructors / Deconstructor

Menu::Menu()
{
    texture_handler = nullptr;
    active = false;

    Debug::log("[WARN] Menu.DefaultConstruct -> Default Constructor used, "
        "initializing null pointers");
}

Menu::Menu(TextureHandler* _texture_handler)
{
    texture_handler = _texture_handler;
    active = false;
}

void Menu::update() {}

void Menu::render() {}
