#define SDL_MAIN_HANDLED

#include <nlohmann/json.hpp>

#include "Debug.h"
#include "Fahm.h"
#include "Random.h"

int main()
{

    Random::seed_random();
    Debug::clear();
    
    Fahm fahm = Fahm("Fahm");
    fahm.start();


    return 0;
}
