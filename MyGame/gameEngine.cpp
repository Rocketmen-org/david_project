#include "gameEngine.h"

// Constructor
GameEngine::GameEngine()
{
  game_window = NULL;
  game_renderer = NULL;
}

GameEngine::~GameEngine()
{}

// Initializes the game engine by initializing SDL,
//  creating the window, and creating the renderer.
// Also initializes all objects.
void GameEngine::init()
{
  if( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
  {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
  }

  //Enable gpu_enhanced textures
  IMG_Init(IMG_INIT_PNG);

  game_window = SDL_CreateWindow("my_game",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                get_screen_width(),
                get_screen_height(), 0);
  game_renderer = SDL_CreateRenderer(game_window,-1,0);

  // Game is running!
  game_is_running = true;

  // Create world map
  World = new Map();
  World->map_init(game_renderer);
  World->read_map();

  // Initialize background image(s)
  BG_space = new BGLayer();
  BG_space->BGLayer_init("./bg_layer1.png", game_renderer );

  BG_moon_distant = new BGLayer();
  BG_moon_distant->BGLayer_init("./bg_layer2.png", game_renderer );

  BG_moon_close = new BGLayer();
  BG_moon_close->BGLayer_init("./bg_layer3.png", game_renderer );

  // Create objects
  alien = new GameObject();
  alien->obj_init("./alien_sprites.png", game_renderer, 100, 100);


};

// Handles any event given to the game engine.
// *** Right now this only works for a character object...
void GameEngine::handleEvents()
{
  SDL_Event game_event;
  SDL_PollEvent(&game_event);

  // Player closes the window ; game is not running
  if(game_event.type == SDL_QUIT) game_is_running = false;

  // State machine!...?
  // *** Figure out how to give SDL a freaking brain and recognize
  //      that I'm holding a key down and not rapidly pressing it over and over
  //      so that the character movement is actually smooth.... eventually
  if( alien->obj_get_state() != "JUMP" )
  {
    switch( game_event.key.keysym.sym )
      {
      case SDLK_UP:
        alien->obj_set_previous_state( alien->obj_get_state() );
        alien->obj_set_state("JUMP");
        alien->obj_set_jump_vel( -(alien->obj_get_obj_grav()) );
        break;

      case SDLK_RIGHT:
        alien->obj_set_previous_state( alien->obj_get_state() );
        alien->obj_set_state("MOVE_RIGHT");
        alien->obj_set_x_vel( alien->obj_get_x_vel()+4 );
        break;

      case SDLK_LEFT:
        alien->obj_set_previous_state( alien->obj_get_state() );
        alien->obj_set_state("MOVE_LEFT");
        alien->obj_set_x_vel( alien->obj_get_x_vel()-4 );
        break;
    }
  }

  if( alien->obj_get_x_vel() == 0
      && alien->obj_get_y_vel() == 0
      && alien->obj_get_state() != "JUMP" )
  {
    alien->obj_set_state("IDLE");
  }

};

// Update ALL objects / mechanics.
void GameEngine::updateMechanics()
{
  //std::cout << alien->obj_get_state() <<"\n";

  alien->obj_update();
  double x_camera_move = alien->obj_get_x_vel()/5;
  //double y_camera_move = alien->obj_get_y_vel();///5;

  BG_space->BGLayer_update( x_camera_move, 0);
  BG_moon_distant->BGLayer_update( x_camera_move*2, 0);
  BG_moon_close->BGLayer_update( x_camera_move*4, 0);

  //World->map_update(-(alien->obj_get_x_vel()));



};

// Render ALL objects.
void GameEngine::render()
{
  SDL_RenderClear(game_renderer);

  BG_space->BGLayer_render();
  BG_moon_distant->BGLayer_render();
  BG_moon_close->BGLayer_render();
  World->map_render();
  alien->obj_render();

  SDL_RenderPresent(game_renderer);
};

// Destroys the engine. AHh run!!
void GameEngine::quit()
{
  SDL_DestroyRenderer(game_renderer);
  SDL_DestroyWindow(game_window);

  IMG_Quit();
  SDL_Quit();
};


// Retrieve game_is_running status
bool GameEngine::get_game_is_running()
{
  return game_is_running;
};
// Retrieve SCREEN_WIDTH;
int GameEngine::get_screen_width()
{
  return SCREEN_WIDTH;
};
// Retrieve SCREEN_HEIGHT;
int GameEngine::get_screen_height()
{
  return SCREEN_HEIGHT;
};
