#pragma once

#include <string>

struct Text
{
    std::string content;
    std::string color;

    Text() {}

    Text(std::string _content, std::string _color = "WHITE")
    {
        content = _content;
        color = _color;
    }

    ~Text() {}

};
