#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_engine.h"
#include "metadata_definitions.h"
#include "render.h"

void cap_fps(uint32_t frame_beginning_tick, int target_fps);
void init_SDL(const int width,
              const int height,
              const int pixel_size,
              SDL_Window** return_window,
              SDL_Renderer** return_renderer);

int main(void) {
  const int MS_PER_TICK = 1000;
  const int TARGET_FPS = 20;

  srand(time(NULL));

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  // defined in metadata header
  init_SDL(WIDTH, HEIGHT, PIXEL_SIZE, &window, &renderer);

  Cell cells[HEIGHT][WIDTH];
  set_cells_to_dead(cells);

  cells[1][0] = ALIVE;
  cells[1][1] = ALIVE;
  cells[1][2] = ALIVE;

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      printf("cell at row %i col %i has %i neighbours\n", row, col,
             number_of_live_neighbors(cells, row, col));
      printf("Next tick it will be %s\n",
             next_cell_status(cells, row, col) == ALIVE ? "alive" : "ded");
    }
  }

  uint32_t start_tick = SDL_GetTicks();
  uint32_t current_tick;
  uint32_t frame_beginning_tick;
  bool running = true;
  while (running) {
    frame_beginning_tick = SDL_GetTicks();
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_SPACE: {
            break;
          }
          default:
            break;
        }
      }
    }

    current_tick = SDL_GetTicks();
    if ((current_tick - start_tick) % MS_PER_TICK != 0) {
      continue;
    }

    set_render_color(BLACK, renderer);
    SDL_RenderClear(renderer);

    set_render_color(WHITE, renderer);
    render_cells(cells, PIXEL_SIZE, renderer);

    SDL_RenderPresent(renderer);
    cap_fps(frame_beginning_tick, TARGET_FPS);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}

void cap_fps(uint32_t frame_beginning_tick, int target_fps) {
  int ms_per_frame = 1000.0 / target_fps;
  uint32_t frame_end_tick = SDL_GetTicks();
  int time_to_wait = ms_per_frame - (frame_end_tick - frame_beginning_tick);
  SDL_Delay((time_to_wait > 0) * time_to_wait);
}

void init_SDL(const int width,
              const int height,
              const int pixel_size,
              SDL_Window** return_window,
              SDL_Renderer** return_renderer) {
  const int SCREEN_X_POS = 0;
  const int SCREEN_Y_POS = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  *return_window = SDL_CreateWindow("Conway's Game of Life", SCREEN_X_POS,
                                    SCREEN_Y_POS, width * pixel_size,
                                    height * pixel_size, SDL_WINDOW_OPENGL);
  if (*return_window == NULL) {
    SDL_Log("Could not create a window: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  *return_renderer =
      SDL_CreateRenderer(*return_window, -1, SDL_RENDERER_ACCELERATED);
  if (*return_renderer == NULL) {
    SDL_Log("Could not create a renderer: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}
