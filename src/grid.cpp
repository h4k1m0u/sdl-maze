#include <algorithm>

#include "grid.hpp"

Grid::Grid(SDL_Renderer* renderer) {
  for (int i_row = 0; i_row < N_ROWS; i_row++)
    for (int i_col = 0; i_col < N_COLS; i_col++)
      m_cells[i_row][i_col] = Cell(renderer, i_row, i_col);
}

void Grid::render() {
  for (int i_row = 0; i_row < N_ROWS; i_row++)
    for (int i_col = 0; i_col < N_COLS; i_col++)
      m_cells[i_row][i_col].render();
}

/**
 * @return a pointer to make it easy to modify it in main loop (to visit it)
 */
Cell* Grid::get_cell(int i_row, int i_col) {
  return &m_cells[i_row][i_col];
}

/**
 * @return Pick a random unvisited neighbor or NULL if all have been visited
 */
Cell* Grid::get_random_neighbor(const Cell* current) {
  NeighborsCoords neighbors_coords = current->get_neighbors_coords();

  // ignore visited cells
  auto filter = [this](const std::pair<int, int>& coord) {
    auto [ i_row, i_col ] = coord;
    return !m_cells[i_row][i_col].is_visited();
  };
  NeighborsCoords neighbors_coords_unvisited;
  std::copy_if(neighbors_coords.begin(), neighbors_coords.end(), std::back_inserter(neighbors_coords_unvisited), filter);
  size_t n_neighbors_unvisited = neighbors_coords_unvisited.size();

  if (n_neighbors_unvisited == 0)
    return nullptr;

  // random neighbor
  size_t i_neighbor = rand() % n_neighbors_unvisited;
  auto [ i_row_neighbor, i_col_neighbor ] = neighbors_coords_unvisited[i_neighbor];

  return get_cell(i_row_neighbor, i_col_neighbor);
}

/* Remove wall between current cell & its neighbor */
void Grid::remove_wall(Cell* current, Cell* neighbor) {
  auto [ i_row, i_col ] = current->get_coords();
  auto [ i_row_neighbor, i_col_neighbor ] = neighbor->get_coords();

  if (i_row == i_row_neighbor + 1) {
    // neighbor above
    current->remove_wall(Side::TOP);
    neighbor->remove_wall(Side::BOTTOM);
  }
  else if (i_row == i_row_neighbor - 1) {
    // neighbor below
    current->remove_wall(Side::BOTTOM);
    neighbor->remove_wall(Side::TOP);
  }
  if (i_col == i_col_neighbor + 1) {
    // neighbor on the left
    current->remove_wall(Side::LEFT);
    neighbor->remove_wall(Side::RIGHT);
  }
  if (i_col == i_col_neighbor - 1) {
    // neighbor on the right
    current->remove_wall(Side::RIGHT);
    neighbor->remove_wall(Side::LEFT);
  }
}
