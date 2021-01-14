//#include <iostream>
#include <SDL2/SDL.h>

//TODO: Create Error handling class

int main(int argc, char ** argv){
  // Initialise SDL2
  SDL_Init(SDL_INIT_EVERYTHING);

  // Create Window
  SDL_Window *window =
    SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                     800, 600, SDL_WINDOW_SHOWN);
  //TODO: Test that window was created successfully

  // Create Renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  // TODO: Test that renderer was created successfully

  //Temporary until GL context is added
  // Set the draw color of renderer to green
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

  //update renderer with prior prefix
  SDL_RenderPresent(renderer);

  //wait used until close window hook implemented
  SDL_Delay(3000);

  // On close destroy renderer
  SDL_DestroyRenderer(renderer);
  // On close also destroy window
  SDL_DestroyWindow(window);

  //Close all leftover SDL systems
  SDL_Quit();

  return 0;
}
