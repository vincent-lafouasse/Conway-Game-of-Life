#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "metadata_definitions.h"

typedef enum {DEAD = 0, ALIVE = 1} Cell;

void set_cells_to_dead(Cell cells[HEIGHT][WIDTH]);
void randomize_cells(Cell cells[HEIGHT][WIDTH], float life_ratio);
