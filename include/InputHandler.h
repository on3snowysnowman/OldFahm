#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <functional>
#include <map>


/**
 * @brief Used to store inidividual elements for the input handler. This holds
 * data such as an id, which represents the int it represents, how many frames
 * this key should exist in the input handler, and the frame delay between 
 * each key press before it will be allowed to be pressed again
 */
struct Key
{
    int id; // The int this key represents
    
    /**
     * @brief Number of frames this key has been pressed without being released
     */
    int frames_active;

    /**
     * @brief // Number of frames this key will be not be allowed to be used
     * until
     */
    int frames_delay; 

    Key() 
    {
        id = 0;
        frames_active = 0;
        frames_delay = 0;
    }
    
    Key(int _id) 
    {
        id = _id;
        frames_active = 0;
        frames_delay = 0;
    }
    
    ~Key() {}

};

/**
 * @brief Handles all pressed keys from the user, and if assigned a frame delay 
 * to a specific key, disallows the user from using that key again until the 
 * amount of target frames has elapsed. Stores 'Key' pointers as data for 
 * pressed keys
 */
class InputHandler
{

private:

    /**
     * @brief Key values that are pressed to their respective key objects
     */
    std::map<int, Key*> keys;


public:

    InputHandler();
    ~InputHandler();

    void update();
    void set_delay(int i, int frames = 15);

    /**
     * @brief Adds a key to the key map if it is not already present
     * 
     * @param key Key to add
     */
    void add_key(int key);
    void remove_key(int key);

    /**
     * @brief Returns a vector of Key pointers that are pressed by the user, 
     * and are available to be used
     * 
     * @return Vector of Key pointers
     */
    std::vector<Key*> get_active_keys();

    /**
     * @brief Returns a vector of Key points that are pressed by the user, 
     * regardless if they are available or not
     * 
     */
    std::vector<Key*> get_raw_pressed_keys();

};