#include "game_engine.h"
#include <stdbool.h>

void advance_to_next_state(Cell cells[HEIGHT][WIDTH],
                           Cell buffer[HEIGHT][WIDTH]) {
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      buffer[row][col] = next_cell_status(cells, row, col);
    }
  }
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      cells[row][col] = buffer[row][col];
    }
  }
}

Cell next_cell_status(Cell cells[HEIGHT][WIDTH], int row, int col) {
  Cell this_cell = cells[row][col];
  int n_live_neighbors = number_of_live_neighbors(cells, row, col);
  if (this_cell == ALIVE) {
    if (n_live_neighbors == 2 || n_live_neighbors == 3) {
      return ALIVE;
    } else {
      return DEAD;
    }
  } else {
    if (n_live_neighbors == 3) {
      return ALIVE;
    } else {
      return DEAD;
    }
  }
}

int number_of_live_neighbors(Cell cells[HEIGHT][WIDTH], int row, int col) {
  int neighboring_rows[] = {(row + HEIGHT - 1) % HEIGHT, row,
                            (row + 1) % HEIGHT};
  int neighboring_cols[] = {(col + WIDTH - 1) % WIDTH, col, (col + 1) % WIDTH};
  int n_live_neighbors = 0;

  for (int row_idx = 0; row_idx < 3; row_idx++) {
    for (int col_idx = 0; col_idx < 3; col_idx++) {
      int neighbor_row = neighboring_rows[row_idx];
      int neighbor_col = neighboring_cols[col_idx];
      if (cells[neighbor_row][neighbor_col] == ALIVE &&
          !(row == neighbor_row && col == neighbor_col)) {
        n_live_neighbors++;
      }
    }
  }
  return n_live_neighbors;
}

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
