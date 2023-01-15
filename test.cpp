#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("Carrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Set the render draw color to green

  // Draw the top of the carrot
  SDL_Rect topRect;
  topRect.x = WINDOW_WIDTH / 2 - 50;
  topRect.y = WINDOW_HEIGHT / 2 - 150;
  topRect.w = 100;
  topRect.h = 100;
  SDL_RenderFillRect(renderer, &topRect);

  // Draw the middle of the carrot
  SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);  // Set the render draw color to orange
  SDL_Rect middleRect;
  middleRect.x = WINDOW_WIDTH / 2 - 75;
  middleRect.y = WINDOW_HEIGHT / 2 - 50;
  middleRect.w = 150;
  middleRect.h = 150;
  SDL_RenderFillRect(renderer, &middleRect);

  // Draw the bottom of the carrot
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Set the render draw color to red
  SDL_Rect bottomRect;
  bottomRect.x = WINDOW_WIDTH / 2 - 100;
  bottomRect.y = WINDOW_HEIGHT / 2;
  bottomRect.w = 200;
  bottomRect.h = 100;
  SDL_RenderFillRect(renderer, &bottomRect);

  // Draw the point of the carrot
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Set the render draw color to red
  SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 75);

  SDL_RenderPresent(renderer);

  SDL_Delay(3000);  // Wait for 3 seconds before closing the window

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
