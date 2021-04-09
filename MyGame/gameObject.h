#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.h"

class GameObject
{
public:
  GameObject();
  ~GameObject();

  void obj_init( std::string, SDL_Renderer*, double, double );
  void obj_update();
  void obj_render();
  void obj_quit();

  std::string obj_get_state();
  void obj_set_state(std::string);

  std::string obj_get_previous_state();
  void obj_set_previous_state(std::string);

  double obj_get_x_vel();
  void obj_set_x_vel(double);

  double obj_get_y_vel();
  void obj_set_y_vel(double);

  double obj_get_max_vel();
  void obj_set_max_vel(double);

  double obj_get_obj_grav();
  void obj_set_obj_grav(double);

  double obj_get_jump_vel();
  void obj_set_jump_vel(double);


private:
  SDL_Renderer* obj_renderer;   // Object's renderer.
  SDL_Texture* obj_graphic;     // Object's graphic.
  SDL_Rect obj_rect;            // Object's rect.

  Sprite* obj_sprite;           // An instance of a Sprite class that controls frame_rect.
  SDL_Rect frame_rect;          // AKA Source rectangle in the sprite sheet.
  SDL_RendererFlip flip_sprite; // Determines whether or not to flip the sprite.

  std::string obj_state;        // Current state of the object.
  std::string obj_pre_state;    // Previous state of the object.

  double initial_x;      // Initial starting x position; kindof archaic
  double initial_y;      // Initial starting y position; kindof archaic

  double x_vel;           // Current horizontal velocity.
  double y_vel;           // Current vertical velocity -- keeps track of jump_vel
  double obj_grav;        // Rate at which obj will fall / y_vel will approach max_vel

  double jump_vel;        // How high the object is able to jump.

  double obj_max_vel;     // Terminal velocity relative to this object


  // putting these here since I can't figure out how to put
  // them in Engine.h and have it in the scope of gameObject.cpp yet >:(
  const double SCREEN_WIDTH = 1200;
  const double SCREEN_HEIGHT = 800;

};
