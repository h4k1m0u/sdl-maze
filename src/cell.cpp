#include "cell.hpp"
#include "constants.hpp"

using namespace Constants;

Cell::Cell(SDL_Renderer* renderer, int i_row, int i_col):
  m_renderer(renderer),
  m_i_row(i_row),
  m_i_col(i_col),
  m_x(i_col * WIDTH_CELL),
  m_y(i_row * HEIGHT_CELL),
  m_walls({
    { Side::TOP, true },
    { Side::RIGHT, true },
    { Side::BOTTOM, true },
    { Side::LEFT, true },
  }),
  m_visited(false)
{
}

bool Cell::is_visited() const {
  return m_visited;
}

std::pair<int, int> Cell::get_coords() const {
  return std::make_pair(m_i_row, m_i_col);
}

void Cell::visit() {
  m_visited = true;
}

void Cell::render() {
  // show visited in different color (for debugging)
  if (m_visited) {
    SDL_SetRenderDrawColor(m_renderer, COLOR_VISITED.r, COLOR_VISITED.g, COLOR_VISITED.b, COLOR_VISITED.a);
    SDL_Rect rect = { m_x, m_y, WIDTH_CELL, HEIGHT_CELL };
    SDL_RenderFillRect(m_renderer, &rect);
  }

  SDL_SetRenderDrawColor(m_renderer, COLOR_CELL.r, COLOR_CELL.g, COLOR_CELL.b, COLOR_CELL.a);

  if (m_walls[Side::TOP])
    SDL_RenderDrawLine(m_renderer, m_x, m_y, m_x + WIDTH_CELL, m_y);

  if (m_walls[Side::RIGHT])
    SDL_RenderDrawLine(m_renderer, m_x + WIDTH_CELL, m_y, m_x + WIDTH_CELL, m_y + HEIGHT_CELL);

  if (m_walls[Side::BOTTOM])
    SDL_RenderDrawLine(m_renderer, m_x + WIDTH_CELL, m_y + HEIGHT_CELL, m_x, m_y + HEIGHT_CELL);

  if (m_walls[Side::LEFT])
    SDL_RenderDrawLine(m_renderer, m_x, m_y + HEIGHT_CELL, m_x, m_y);
}

NeighborsCoords Cell::get_neighbors_coords() const {
  NeighborsCoords neighbors;

  if (m_i_row > 0) {
    std::pair<int, int> coords_top(m_i_row - 1, m_i_col);
    neighbors.push_back(coords_top);
  }

  if (m_i_col < N_COLS - 1) {
    std::pair<int, int> coords_right(m_i_row, m_i_col + 1);
    neighbors.push_back(coords_right);
  }

  if (m_i_row < N_ROWS - 1) {
    std::pair<int, int> coords_bottom(m_i_row + 1, m_i_col);
    neighbors.push_back(coords_bottom);
  }

  if (m_i_col > 0) {
    std::pair<int, int> coords_left(m_i_row, m_i_col - 1);
    neighbors.push_back(coords_left);
  }

  return neighbors;
}

void Cell::remove_wall(Side side) {
  m_walls[side] = false;
}
