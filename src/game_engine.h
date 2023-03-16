#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "metadata_definitions.h"

typedef enum {DEAD = 0, ALIVE = 1} Cell;

void advance_to_next_state(Cell cells[HEIGHT][WIDTH], Cell buffer[HEIGHT][WIDTH]);
Cell next_cell_status(Cell cells[HEIGHT][WIDTH], int row, int col);
int number_of_live_neighbors(Cell cells[HEIGHT][WIDTH], int row, int col);
void set_cells_to_dead(Cell cells[HEIGHT][WIDTH]);
void randomize_cells(Cell cells[HEIGHT][WIDTH], float life_ratio);
