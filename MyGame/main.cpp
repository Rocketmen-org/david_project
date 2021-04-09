#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "gameEngine.h"

int main()
{
  GameEngine* ge = new GameEngine();

  ge->init();

  int this_start_time, this_duration = 0;
  const int frame_duration = 1000/60;

  while( ge->get_game_is_running() )
  {
    // Begin to check time
    this_start_time = SDL_GetTicks();

    ge->handleEvents();
    ge->updateMechanics();
    ge->render();

    // End of check time
    // Begin to limit FPS
    this_duration = SDL_GetTicks() - this_start_time;

    if( this_duration < frame_duration)
    {
      SDL_Delay( frame_duration - this_duration );
    }

  }

  ge->quit();

  return 0;
}
