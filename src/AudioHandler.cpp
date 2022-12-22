#include "AudioHandler.h"

// Static Members

bool AudioHandler::initialized = false;


// Public Members

void AudioHandler::init_audio(int frequency, int channels, 
    int chunksize)
{
    if(Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize)
        < 0)
    {
        Debug::log("[ERR] Failed to initialized SDL Mixer");
        exit(0);
    }
}

void AudioHandler::play_audio(const char* path)
{
    
}


