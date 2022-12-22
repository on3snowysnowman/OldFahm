#pragma once

#include <SDL2/SDL_mixer.h>
#include <list>

#include "Debug.h"

class AudioHandler
{

public:

    static void init_audio(int frequency = 44100, int channels = 2, 
        int chunksize = 2048);

    static void play_audio(const char* path);

    static void quit();

private:

    static bool initialized;

    static std::list<std::string> sounds_to_play;

};
