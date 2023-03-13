#pragma once

#include <SDL2/SDL.h>

#define WIDTH 30
#define HEIGHT 30

#define DEAD 0
#define ALIVE 1

typedef enum { BLACK, WHITE } Color;

void set_render_color(Color color, SDL_Renderer* renderer);

void render_cell(int row, int col, int pixel_size, SDL_Renderer* renderer);

void render_cells(uint8_t cells[HEIGHT][WIDTH],
                  int pixel_size,
                  SDL_Renderer* renderer);
