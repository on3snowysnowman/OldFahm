#pragma once

#include <string>

struct DisplayCharacter
{
    int tile_id;
    std::string color;

    DisplayCharacter()
    {
        tile_id = ' ';
        color = "White";
    }

    DisplayCharacter(int _tile_id, std::string _color)
    {
        tile_id = _tile_id;
        color = _color;
    }
};