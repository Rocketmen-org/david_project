#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

class Sprite
{
public:

  Sprite();
  ~Sprite();

  void sprite_init(std::string graphic, SDL_Renderer* ren,
    int frames, int frame_duration, int start_width, int start_height);
  SDL_Rect sprite_update(double,double);
  void sprite_render(SDL_Renderer* ren);
  void sprite_quit();

private:
  SDL_Texture* sprite_graphic;    // The graphic / source img
  SDL_Rect frame_rect;            // The rect that scouts the source img

  int frame = 0;                  // Which frame the sprite is on

  int frame_count;                // Used for updating 'frame'
  int frame_duration;

  SDL_Renderer* game_renderer;


};
