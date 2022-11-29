#pragma once

#include <string>

#include "OJAsciiEngine.h"
#include "Windows/AllWindows.h"
#include "Tilemap.h"

class Fahm : public ojae::OJAsciiEngine
{

public:

    Fahm(const char* title);
    ~Fahm();

    void start();

private:

    Tilemap* tilemap;

    TilemapWindow* tilemap_window;

    void startup_screen();
    void handle_queue_events();
    void handle_key_press();
    void update() override;
    void render() override;
    
};
