#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

class BGLayer
{


public:
  BGLayer();
  ~BGLayer();

  void BGLayer_init(std::string img, SDL_Renderer* ren );
  void BGLayer_update(double,double);
  void BGLayer_render();

private:

  SDL_Renderer* bg_renderer;   // Layer's renderer.
  SDL_Texture* bg_graphic;     // Layer's graphic.

  SDL_Rect bg_phs_rect;        // Layer's rect.

  SDL_Rect bg_img_rect;        // Rect that scouts the bg_graphic

  const double SCREEN_WIDTH = 1200;
  const double SCREEN_HEIGHT = 800;

  const double BG_IMG_WIDTH = 2400;
  const double BG_IMG_HEIGHT = 800;
};
