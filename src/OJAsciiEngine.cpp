#include "OJAsciiEngine.h"
#include "Debug.h"
#include "nlohmann/json.hpp"
#include "Jloader.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/ColliderComponent.h"

#ifdef _WIN32
#include <wtypes.h>
#endif


// Constructors / Deconstructor

ojae::OJAsciiEngine::OJAsciiEngine(const char* title)
{

    nlohmann::json settings_json = Jloader::get("data/ojae_settings.json");

    #ifdef _WIN32

    RECT desktop;

    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    screen_width = desktop.right;
    screen_height = desktop.bottom;
    
    #else

    screen_width = settings_json["screen width"];
    screen_height = settings_json["screen height"];

    #endif

    if(screen_width < 500 ||
        screen_height < 500)
    {
        Debug::log("[ERR] Minimum screen dimensions are 500 x 500 pixels, "
            "but are set to the value: ", false, true);
        Debug::log(screen_width, false, false);
        Debug::log(" x ", false, false);
        Debug::log(screen_height, false, false);
        Debug::log(". This can be changed in the file: \"settings.json\" under "
            " the directory: DnDTool/data/settings.json -> screen_height "
            " and screen_width", false, false);
        exit(0);
    }

    running = false;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Debug::log("[ERR] SDL Failed to Init");
        exit(0);
    }

    int r = settings_json["background color"].at(0);
    int g = settings_json["background color"].at(1);
    int b = settings_json["background color"].at(2);

    window = SDL_CreateWindow(title, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        screen_width, screen_height, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    texture_handler = new TextureHandler(renderer);
    input_handler = new InputHandler();

    // get_fonts("data/available_fonts.json");

    std::string targ_path;
    
    load_colors(std::string(
        settings_json["color path"]).c_str());

    Debug::log("[OUT] OJAsciiEngine Initialized");
}

ojae::OJAsciiEngine::~OJAsciiEngine()
{
    delete texture_handler;
}


// Public Members

void ojae::OJAsciiEngine::start_OJAE()
{
    running = true;
    simulation_loop();
}

// Protected Members

void ojae::OJAsciiEngine::simulation_loop()
{
    while(running)
    {
        frame_start = SDL_GetTicks64();

        handle_events();
        input_handler->update();
        update();
        render();

        frame_time = SDL_GetTicks64() - frame_start;

        if(FRAME_DELAY > frame_time)
        {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }

    quit();
}

void ojae::OJAsciiEngine::clear_screen()
{
    SDL_RenderClear(renderer);
}

void ojae::OJAsciiEngine::draw_to_screen()
{
    SDL_RenderPresent(renderer);
}

void ojae::OJAsciiEngine::set_key_delay(int key, int frames)
{
    input_handler->set_delay(key, frames);
}

void ojae::OJAsciiEngine::update() {}

void ojae::OJAsciiEngine::render() {}

void ojae::OJAsciiEngine::quit() 
{
    SDL_Quit();
}

std::vector<int> ojae::OJAsciiEngine::get_pressed_keys()
{
    std::vector<int> pressed_keys;

    for(Key* k : input_handler->get_active_keys())
    {
        pressed_keys.push_back(k->id);
    }

    return pressed_keys; 
}

std::vector<int> ojae::OJAsciiEngine::get_raw_pressed_keys()
{
    return raw_pressed_keys;
}

// Private Members

void ojae::OJAsciiEngine::handle_events()
{
    raw_pressed_keys.clear();

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            running = false;
        }

        else if(event.type == SDL_KEYDOWN)
        {
            input_handler->add_key(event.key.keysym.sym);
            raw_pressed_keys.push_back(event.key.keysym.sym);
        }

        else if(event.type == SDL_KEYUP)
        {
            input_handler->remove_key(event.key.keysym.sym);
        }
    }
}

void ojae::OJAsciiEngine::load_colors(const char* path)
{
    // If the file does not exist
    if(!Debug::file_exists(path))
    {
        Debug::log("[ERR] OJAsciiEngine.get_colors -> Could not open file: ",
            false, true);
        Debug::log(path, false, false);
        exit(0);
    }

    // Get the json object from the colors file
    nlohmann::json j_loader = Jloader::get(path);

    // Iterate through the colors in the json object and add them to the 
    // TextureHandler
    for(nlohmann::json::iterator it = j_loader.begin(); it != j_loader.end();
        it++)
    {
        Debug::log("[OUT] Loading Color: ", false, true);
        Debug::log(std::string(it.key()), true, false);

        texture_handler->add_color(new Color(it.key(), it.value()[0], 
            it.value()[1], it.value()[2]));
    }
}


