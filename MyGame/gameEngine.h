#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "gameObject.h"
#include "MapManager.h"
#include "BGLayer.h"

class GameEngine
{
public:
  GameEngine();
  ~GameEngine();

  void init();
  void handleEvents();
  void updateMechanics();
  void render();
  void quit();

  bool get_game_is_running();
  int  get_screen_width();
  int  get_screen_height();

private:
  SDL_Window* game_window;
  SDL_Renderer* game_renderer;

  const int SCREEN_WIDTH = 1200;
  const int SCREEN_HEIGHT = 800;

  bool game_is_running; // Whether the game is running or not.

  GameObject* alien;    // Alien.
  Map* World;
  BGLayer* BG_space;
  BGLayer* BG_moon_distant;
  BGLayer* BG_moon_close;

};
