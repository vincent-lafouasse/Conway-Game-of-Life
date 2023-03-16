#pragma once

#include <SDL2/SDL.h>
#include "metadata_definitions.h"
#include "game_engine.h"

typedef enum { BLACK, WHITE } Color;

void set_render_color(Color color, SDL_Renderer* renderer);

void render_cell(int row, int col, int pixel_size, SDL_Renderer* renderer);

void render_cells(Cell cells[HEIGHT][WIDTH],
                  int pixel_size,
                  SDL_Renderer* renderer);
