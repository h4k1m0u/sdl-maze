#ifndef CELL_HPP
#define CELL_HPP

#include <SDL2/SDL_render.h>
#include <unordered_map>

#include "side.hpp"
#include "types.hpp"

class Cell {
public:
  Cell() = default;
  Cell(SDL_Renderer* renderer, int i_row, int i_col);

  bool is_visited() const;
  std::pair<int, int> get_coords() const;

  void visit();
  void render();
  NeighborsCoords get_neighbors_coords() const;
  void remove_wall(Side side);

private:
  SDL_Renderer* m_renderer;
  int m_i_row;
  int m_i_col;
  int m_x;
  int m_y;
  std::unordered_map<Side, bool> m_walls;
  bool m_visited;
};

#endif // CELL_HPP
