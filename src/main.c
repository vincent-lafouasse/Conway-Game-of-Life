#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "render.h"

#define WIDTH 30
#define HEIGHT 30

#define DEAD 0
#define ALIVE 1

int main(void) {
  const int PIXEL_SIZE = 10;
  const int SCREEN_X_POS = 0;
  const int SCREEN_Y_POS = 0;
  const int MS_PER_TICK = 1000;
  const int TARGET_FPS = 20;
  const int MS_PER_FRAME = 1000.0 / TARGET_FPS;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Window* window = SDL_CreateWindow("Conway's Game of Life", SCREEN_X_POS,
                                        SCREEN_Y_POS, WIDTH * PIXEL_SIZE,
                                        HEIGHT * PIXEL_SIZE, SDL_WINDOW_OPENGL);
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

  uint8_t cells[HEIGHT][WIDTH] = {DEAD};
  cells[0][5] = ALIVE;
  cells[29][5] = ALIVE;

  uint32_t start_tick = SDL_GetTicks();
  uint32_t current_tick;
  uint32_t frame_beginning_tick;
  uint32_t frame_end_tick;

  bool running = true;
  while (running) {
    frame_beginning_tick = SDL_GetTicks();
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }
    }

    current_tick = SDL_GetTicks();
    if ((current_tick - start_tick) % MS_PER_TICK != 0) {
      continue;
    }

    SDL_Log("a frame is passing");

    set_render_color(BLACK, renderer);
    SDL_RenderClear(renderer);

    set_render_color(WHITE, renderer);
    render_cells(cells, PIXEL_SIZE, renderer);

    SDL_RenderPresent(renderer);

    frame_end_tick = SDL_GetTicks();
    int time_to_wait = MS_PER_FRAME - (frame_end_tick - frame_beginning_tick);
    SDL_Delay((time_to_wait > 0) * time_to_wait);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
