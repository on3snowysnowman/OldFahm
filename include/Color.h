#pragma once 

#include <string>
#include <cstdlib>

/**
 * @brief Contains data for a Color. Holds rgb values and a name
 */
class Color
{

private:

    std::string name; // Name of the color

    int r; // Red value of the Color
    int g; // Green value of the Color
    int b; // Blue value of the Color

public:

    Color() 
    {
        name = "Default";

        r = 0;
        g = 0;
        b = 0;
    }

    Color(std::string _name, int _r, int _g, int _b) 
    {
        name = _name;

        set_values(_r, _g, _b);
    }

    ~Color() {}

    std::string get_name() { return name; }

    int get_r() { return r; }

    int get_g() { return g; }

    int get_b() { return b; }

    /**
     * @brief Sets new color values for this Color
     * 
     * @param _r Red value
     * @param _g Green value
     * @param _b Blue value
     */
    void set_values(int _r, int _g, int _b)
    {
        // Take the absolute value of the parameters so they are garunteed 
        // not negative
        _r = abs(_r);
        _g = abs(_g);
        _b = abs(_b);
            
        // Check if the values exceed the color channel limit of 255
        if(_r > 255) { _r = 255; }
        if(_g > 255) { _g = 255; }
        if(_b > 255) {_b = 255; }

        r = _r;
        g = _g;
        b = _b;
    }
};
