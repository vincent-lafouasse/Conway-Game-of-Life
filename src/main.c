#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 30
#define HEIGHT 30

void render_cell(int row, int col, int pixel_size, SDL_Renderer* renderer) {
  SDL_Rect cell_rect = {row * pixel_size, col * pixel_size, pixel_size,
                        pixel_size};
  SDL_RenderDrawRect(renderer, &cell_rect);
}

int main(void) {
  const int PIXEL_SIZE = 10;
  const int SCREEN_X_POS = 0;
  const int SCREEN_Y_POS = 0;
  const int MS_PER_TICK = 1000;

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

  uint8_t cells[HEIGHT][WIDTH] = {false};
  cells[0][5] = true;
  cells[29][5] = true;

  bool running = true;
  uint32_t start_tick = SDL_GetTicks();
  uint32_t current_tick;
  while (running) {
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int row = 0; row < HEIGHT; row++) {
      for (int col = 0; col < WIDTH; col++) {
        if (cells[row][col]) {
          render_cell(row, col, PIXEL_SIZE, renderer);
        }
      }
    }

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
