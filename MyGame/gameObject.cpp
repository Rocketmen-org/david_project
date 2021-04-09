#include "gameObject.h"

//
GameObject::GameObject()
{}

//
GameObject::~GameObject()
{}

// Initializes the object by creating a surface, creating a texture
//  from that surface, and then freeing the surface.
void GameObject::obj_init( std::string img, SDL_Renderer* ren, double w, double h)
{
  // Bind this object to the renderer
  obj_renderer = ren;

  // Give the object a texture
  SDL_Surface* temp = IMG_Load(img.c_str());
  obj_graphic = SDL_CreateTextureFromSurface(ren, temp);
  SDL_FreeSurface(temp);

  // Construct the objects' initial rect
  obj_rect.x = (SCREEN_WIDTH/2)-(w/2);
  obj_rect.y = 500-h;
  obj_rect.w = w;
  obj_rect.h = h;

  // Sprite stuff
  obj_sprite = new Sprite();
  obj_sprite->sprite_init(img, ren, 4, 100, w, h );
  flip_sprite = SDL_FLIP_NONE;

  // Set the objects initial state as well as initial x and y value
  obj_state = "IDLE";
  initial_x = obj_rect.x;
  initial_y = obj_rect.y;

  // Set the max velocity of the object
  x_vel = 0;
  y_vel = 0;
  obj_max_vel = 15;

  // Set the objects personal gravity and jump velocity
  // Remember positive values move object down for some forsaken reason
  obj_grav = 25;
  jump_vel = 25;

}


// Updates any information about the object.
void GameObject::obj_update()
{

  // Object moves horizontally first.
  obj_rect.x += x_vel;

  // If the object's state is JUMP, begin jump action
  if( obj_state == "JUMP" )
  {
    // Object moves up
    obj_rect.y += jump_vel;
    y_vel = jump_vel;

    // If gravity force isn't reached, strive for it
    if( jump_vel != obj_grav )
    {
      jump_vel += 1;
    }

  }

  // When character hits the ground, the JUMP state is over.
  if( obj_rect.y >= initial_y )
  {
    obj_state = obj_pre_state;
    y_vel = 0;
  }

  // Check borders
  if (obj_rect.x > SCREEN_WIDTH - obj_rect.w - 100) obj_rect.x = SCREEN_WIDTH - obj_rect.w - 100;
  if (obj_rect.x < 100) obj_rect.x = 100;

//if (obj_rect.y < (SCREEN_HEIGHT/5) ) obj_rect.y = (SCREEN_HEIGHT/5);
  if (obj_rect.y > (SCREEN_HEIGHT/5) * 4 ) obj_rect.y = (SCREEN_HEIGHT/5) * 4;


  // Decay x_vel by striving for 0
  if( x_vel > 0 )
  {
    x_vel-=0.2;
    if( x_vel < 0 )
    {
      x_vel = 0;
    }
  }
  if( x_vel < 0 )
  {
    x_vel+=0.2;
    if( x_vel > 0 )
    {
      x_vel = 0;
    }
  }


  //Update the flip_sprite var depending on current velocity
  //Doing this instead of based on state so that it looks nice with JUMP state
  if (x_vel > 0 ){ flip_sprite = SDL_FLIP_NONE; }
  if (x_vel < 0 ){ flip_sprite = SDL_FLIP_HORIZONTAL; }



}

// Renders the object onto the screen.
void GameObject::obj_render()
{
  frame_rect = obj_sprite->sprite_update(x_vel,y_vel);
  SDL_RenderCopyEx( obj_renderer, obj_graphic, &frame_rect, &obj_rect, 0.0, NULL, flip_sprite );
}

// Destroys the object.
void GameObject::obj_quit()
{
//idk wat to put here yet lol
}

// G/S for obj_state
std::string GameObject::obj_get_state()
{
  return obj_state;
}
void GameObject::obj_set_state(std::string new_state)
{
  obj_state = new_state;
}

// G/S for obj_pre_state
std::string GameObject::obj_get_previous_state()
{
  return obj_pre_state;
}
void GameObject::obj_set_previous_state(std::string incoming_state)
{
  obj_pre_state = incoming_state;
}

// G/S for x_vel
double GameObject::obj_get_x_vel()
{
  return x_vel;
}
void GameObject::obj_set_x_vel(double x_vel)
{
  if( x_vel <= obj_max_vel && x_vel >= -obj_max_vel )
  {
    this->x_vel = x_vel;
  }
}

// G/S for y_vel
double GameObject::obj_get_y_vel()
{
  return y_vel;
}
void GameObject::obj_set_y_vel(double y_vel)
{
  if( y_vel <= obj_max_vel )
  {
    this->y_vel = y_vel;
  }
}

// G/S for obj_grav
double GameObject::obj_get_obj_grav()
{
  return obj_grav;
}
void GameObject::obj_set_obj_grav(double g)
{
  obj_grav = g;
}

// G/S for jump_str
double GameObject::obj_get_jump_vel()
{
  // This needs to be negative so that it returns a value that makes obj go up :)
  return jump_vel;
}
void GameObject::obj_set_jump_vel(double s)
{
  jump_vel = s;
}

// G/S for max_vel
double GameObject::obj_get_max_vel()
{
  return obj_max_vel;
}
void GameObject::obj_set_max_vel(double v)
{
  obj_max_vel = v;
}
