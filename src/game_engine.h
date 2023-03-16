#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "metadata_definitions.h"

void set_cells_to_dead(uint8_t cells[HEIGHT][WIDTH]);
void randomize_cells(uint8_t cells[HEIGHT][WIDTH], float life_ratio);
