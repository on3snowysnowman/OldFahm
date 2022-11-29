#pragma once

#include <string>

struct DisplayCharacter
{
    int symbol;
    std::string color;

    DisplayCharacter()
    {
        symbol = ' ';
        color = "White";
    }

    DisplayCharacter(int _symbol, std::string _color)
    {
        symbol = _symbol;
        color = _color;
    }
};