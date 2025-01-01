#ifndef GRID_HPP
#define GRID_HPP

#include "cell.hpp"
#include "constants.hpp"

using namespace Constants;

class Grid {
public:
  Grid(SDL_Renderer* renderer);
  void render();

  Cell* get_cell(int i_row, int i_col);
  Cell* get_random_neighbor(const Cell* current);
  void remove_wall(Cell* current, Cell* neighbor);

private:
  Cell m_cells[N_ROWS][N_COLS];
};

#endif // GRID_HPP
