#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <SDL2/SDL.h>

int main()
{

    Uint64 start;
    int elapsed;
   
   std::vector<int> vec;
   std::map<int, int> mapp;

   for(int i = 0; i < 1000000; i++)
   {
        vec.push_back(i);
        mapp.emplace(i, i);
   }


   start = SDL_GetTicks64();

   for(int i : vec)
   {
        ;
   }

   elapsed = SDL_GetTicks64() - start;

   std::cout << "Vector: " << elapsed << '\n';

   start = SDL_GetTicks64();

   for(std::pair<int,int> element : mapp)
   {
    ;
   }

   elapsed = SDL_GetTicks64();

   std::cout << "Map: " << elapsed;

    return 0;
}