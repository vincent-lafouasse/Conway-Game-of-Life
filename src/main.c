#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  const int SCREEN_WIDTH = 30;
  const int SCREEN_HEIGHT = 30;
  const int PIXEL_SIZE = 10;
  const int SCREEN_X_POS = 0;
  const int SCREEN_Y_POS = 0;
  const int MS_PER_TICK = 1000;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Window* window = SDL_CreateWindow(
      "Conway's Game of Life", SCREEN_X_POS, SCREEN_Y_POS,
      SCREEN_WIDTH * PIXEL_SIZE, SCREEN_HEIGHT * PIXEL_SIZE, SDL_WINDOW_OPENGL);
  if (window == NULL) {
    SDL_Log("Could not create a window: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    SDL_Log("Could not create a renderer: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  bool running = true;
  while (running) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }
    }

    SDL_Delay(MS_PER_TICK);
    SDL_Log("a frame is passing");

    SDL_SetRenderDrawColor(renderer, 147, 112, 219, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
