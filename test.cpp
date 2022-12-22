#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

int main() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << '\n';
    return 1;
  }

  // Initialize SDL_mixer
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "Error initializing SDL_mixer: " << Mix_GetError() << '\n';
    SDL_Quit();
    return 1;
  }

  // Load a WAV file
  Mix_Chunk* sound = Mix_LoadWAV("assets/sound/Snap.wav");
  if (!sound) {
    std::cerr << "Error loading WAV file: " << Mix_GetError() << '\n';
    Mix_CloseAudio();
    SDL_Quit();
    return 1;
  }

  // Play the sound on channel 0
  Mix_PlayChannel(0, sound, 0);

  // Wait until the sound finishes playing
  while (Mix_Playing(0)) {
    SDL_Delay(100);
  }

  // Clean up
  Mix_FreeChunk(sound);
  Mix_CloseAudio();
  SDL_Quit();

  return 0;
}