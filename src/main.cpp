#include <SDL2/SDL.h>
#include <stack>
#include <iostream>

#include "constants.hpp"
#include "grid.hpp"

using namespace Constants;

/* Maze generator */
int main() {
  // SDL2
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    std::cout << "Error init. sdl2: " << SDL_GetError() << '\n';
    std::exit(1);
  }

  SDL_Window* window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  // SDL_RENDERER_ACCELERATED: GPU does the rendering instead of CPU (by default)
  // SDL_RENDERER_PRESENTVSYNC: sync'ed with screen refresh rate (otherwise fps > 1000)
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // unvisited neighbor picked randomly
  srand(time(NULL));

  // grid
  Grid grid(renderer);
  Cell* current = grid.get_cell(0, 0);
  current->visit();
  std::stack<Cell*> stack;

  // main loop
  bool quit = false;

  while (!quit) {
    // process events
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
        quit = true;
      }
    }

    // find unvisited neighbor or get one from the stack
    Cell* neighbor = grid.get_random_neighbor(current);

    if (neighbor != nullptr) {
      stack.push(current);
      grid.remove_wall(current, neighbor);
      current = neighbor;
      current->visit();
    }
    else if (!stack.empty()) {
      current = stack.top();
      stack.pop();
    }

    // clear window
    SDL_SetRenderDrawColor(renderer, COLOR_BG.r, COLOR_BG.g, COLOR_BG.b, COLOR_BG.a);
    SDL_RenderClear(renderer);

    // draw grid
    grid.render();

    SDL_RenderPresent(renderer);
  }

  // free resources
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
