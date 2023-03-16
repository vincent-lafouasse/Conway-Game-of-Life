#include "render.h"
#include <stdint.h>

void set_render_color(Color color, SDL_Renderer* renderer) {
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  uint8_t alpha = 255;

  switch (color) {
    case BLACK:
      break;
    case WHITE:
      red = 255;
      green = 255;
      blue = 255;
      break;
    default:
      break;
  }
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void render_cell(int row, int col, int pixel_size, SDL_Renderer* renderer) {
  SDL_Rect cell_rect = {col * pixel_size, row * pixel_size, pixel_size,
                        pixel_size};
  SDL_RenderFillRect(renderer, &cell_rect);
}

void render_cells(Cell cells[HEIGHT][WIDTH],
                  int pixel_size,
                  SDL_Renderer* renderer) {
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      if (cells[row][col] == ALIVE) {
        render_cell(row, col, pixel_size, renderer);
      }
    }
  }
}
