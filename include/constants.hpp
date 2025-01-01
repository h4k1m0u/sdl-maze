#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SDL2/SDL_pixels.h>

namespace Constants {
  const int N_COLS = 15;
  const int N_ROWS = 15;

  const int WIDTH_CELL = 64;
  const int HEIGHT_CELL = 64;

  const int WINDOW_WIDTH = N_COLS * WIDTH_CELL;
  const int WINDOW_HEIGHT = N_ROWS * HEIGHT_CELL;

  const SDL_Color COLOR_BG = { 0, 0, 0, 0xff };
  const SDL_Color COLOR_CELL = { 0xff, 0xff, 0xff, 0xff };
  const SDL_Color COLOR_VISITED = { 0xff, 0, 0xff, 0xff };
}

#endif
