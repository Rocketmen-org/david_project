#include "BGLayer.h"


BGLayer::BGLayer()
{

}
BGLayer::~BGLayer()
{

}

void BGLayer::BGLayer_init( std::string img, SDL_Renderer* ren )
{

  // Bind this object to the renderer
  bg_renderer = ren;

  // Give the object a texture
  SDL_Surface* temp = IMG_Load(img.c_str());
  bg_graphic = SDL_CreateTextureFromSurface(ren, temp);
  SDL_FreeSurface(temp);

  // Initialize the position of the physical rect
  bg_phs_rect.w = SCREEN_WIDTH;
  bg_phs_rect.h = SCREEN_HEIGHT;
  bg_phs_rect.x = 0;
  bg_phs_rect.y = 0;

  // Initialize the position/size of the rect scouting the bg image
  bg_img_rect.w = SCREEN_WIDTH;
  bg_img_rect.h = SCREEN_HEIGHT;
  bg_img_rect.x = 0;
  bg_img_rect.y = 0;

}

void BGLayer::BGLayer_update(double player_x_vel, double player_y_vel)
{


// Just do looping the cheap way because i couldn't figure
// out how to do it nicely


  //  Move the images
  bg_img_rect.x += player_x_vel;

  if( bg_img_rect.x + SCREEN_WIDTH > BG_IMG_WIDTH )
  {
    bg_img_rect.x = 0;
  }
  else if( bg_img_rect.x < 0 )
  {
    bg_img_rect.x = BG_IMG_WIDTH - SCREEN_WIDTH;
  }




}
void BGLayer::BGLayer_render()
{
  SDL_RenderCopy( bg_renderer, bg_graphic, &bg_img_rect, &bg_phs_rect);


}
