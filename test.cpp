#define SDL_MAIN_HANDLED

#include <vector>
#include <list>
#include <SDL2/SDL.h>
#include <iostream>


class Test
{

};

int main()
{

    std::vector<Test> vec;
    std::list<Test> lis;


    Uint64 init;
    int elapsed;

    for(int i = 0; i < 10000000; i++)
    {
        vec.push_back(Test());
        lis.push_back(Test());
    }

    init = SDL_GetTicks64();

    for(Test t : vec)
    {
        ;
    }

    elapsed = SDL_GetTicks64() - init;

    std::cout << "Vector: " << elapsed << '\n';

    init = SDL_GetTicks64();

    for(Test t : lis)
    {
        ;
    }

    elapsed = SDL_GetTicks64() - init;

    std::cout << "List: " << elapsed << '\n';

    return 0;
}