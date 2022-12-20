#include <iostream>

#include "InputHandler.h"

SDL_Event event;

InputHandler::InputHandler() {}
InputHandler::~InputHandler() {}

void InputHandler::update() 
{
    // Iterate through each Key and deduct 1 frame from its delay
    for(std::map<int,Key*>::iterator it = keys.begin(); it != keys.end(); it++)
    {
        if(it->second->frames_delay == -1) return;

        it->second->frames_delay -= 1;
        if(it->second->frames_delay <= 0)
        {
            // remove_key(it->first);
            it->second->frames_delay = 0;
        }
    }
}

void InputHandler::set_delay(int i, int frames) 
{
    if(keys.count(i) != 0)
    {   
        keys[i]->frames_delay = frames;
    }

    else
    {
        keys[i]->frames_active++;
    }
}


void InputHandler::add_key(int key) 
{
    raw_keys.push_back(Key(key));

    if(keys.count(key) == 0)
    {
        keys[key] = new Key(key);
    }
}

void InputHandler::remove_key(int key) 
{
    if(keys.count(key) != 0)
    {
        delete keys[key];
        keys.erase(key);
    }
}

void InputHandler::clear_raw_keys()
{
    raw_keys.clear();
}

std::vector<Key> InputHandler::get_raw_keys()
{
    return raw_keys;
}

std::vector<Key*> InputHandler::get_active_keys() 
{
    std::vector<Key*> available_keys;

    for(std::map<int, Key*>::iterator it = keys.begin(); it != keys.end(); 
        it++)
    {

        if(it->second->frames_delay == 0)
        {
            available_keys.push_back(it->second);
        }
    }

    return available_keys;
}
