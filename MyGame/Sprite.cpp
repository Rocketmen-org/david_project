#include "Sprite.h"

//
Sprite::Sprite()
{}

//
Sprite::~Sprite()
{}


// Initialize the sprite system for this sprite.
void Sprite::sprite_init( std::string graphic, SDL_Renderer* ren,
   int frames, int frame_duration, int start_width, int start_height )
{

  // Bind this sprite to the object renderer
  game_renderer = ren;

  // Give the object a texture / Set the sprite texture
  SDL_Surface* temp = IMG_Load(graphic.c_str());
  sprite_graphic = SDL_CreateTextureFromSurface(ren, temp);
  SDL_FreeSurface(temp);

  // Set the frames count, duration, as well as the source rectangle.
  this->frame_count = frames;
  this->frame_duration = frame_duration;

  frame_rect.w = 30;   // was 30?
  frame_rect.h = 30; // was 30?
  frame_rect.x = 0;
  frame_rect.y = 0;

}

// Update the sprite, aka the source rectangle.
SDL_Rect Sprite::sprite_update(double obj_velocity, double y_vel)
{
  int frame_time = (int) (SDL_GetTicks() / frame_duration) % frame_count;


  static int last_frame_time = 0;

  // If a new frame is reached,
  if( last_frame_time != frame_time)
  {
    if( frame_time < 1 )  // Reset the sprite x position
    {
      frame_rect.x = 0;
    }
    else
    {
      frame_rect.x += frame_rect.w; // Move the frame rect 1 frame over.
    }

  }
  last_frame_time = frame_time;

  if( y_vel != 0)  // if jumping
  {
    if( y_vel < 0){ frame_rect.y = 2*frame_rect.h; } // going up
    if( y_vel > 0){ frame_rect.y = 3*frame_rect.h; } // going down
  }
  else{
    if( obj_velocity == 0 ){ frame_rect.y = 0; }     // Idle
    else                   { frame_rect.y = frame_rect.h; }    // Moving
  }

  return(frame_rect);
}

void Sprite::sprite_render( SDL_Renderer* ren )
{
  // ???
}


void Sprite::sprite_quit()
{}
