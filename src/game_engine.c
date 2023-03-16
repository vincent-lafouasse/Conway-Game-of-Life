#include "game_engine.h"

void randomize_cells(Cell cells[HEIGHT][WIDTH], float life_ratio) {
  float random_number;
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      random_number = (rand() % 100) / 100.;
      if (random_number < life_ratio) {
        cells[row][col] = ALIVE;
      } else {
        cells[row][col] = DEAD;
      }
    }
  }
}

void set_cells_to_dead(Cell cells[HEIGHT][WIDTH]) {
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      cells[row][col] = DEAD;
    }
  }
}
