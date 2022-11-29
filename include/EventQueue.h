#pragma once

#include <vector>
#include <string>
#include <list>
#include <iostream>

class EventQueue
{
    
public:

    static bool has_events()
    {
        return queue.size() > 0;
    }

    static void place_event(std::string event)
    {
        queue.push_back(event);
    }

    static std::string pull_event()
    {
        if(queue.size() == 0)
        {
            return std::string{};
        }

        std::string targ_event = queue.front();
        queue.erase(queue.begin());
        return targ_event;
    }


private:

    static std::list<std::string> queue;

};

