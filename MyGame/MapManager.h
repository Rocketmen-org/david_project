#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const int LEVEL_WIDTH = 1200;
const int LEVEL_HEIGHT = 800;

//Tile constants
const int TILE_WIDTH = 100;
const int TILE_HEIGHT = 100;
const int TOTAL_TILES = 96;
const int TOTAL_TILE_SPRITES = 8;

//The different tile sprites
const int TILE_DIRT = 00;
const int TILE_GRASS = 01;
const int TILE_BRICK = 02;
const int TILE_DIRT_TO_BRICK = 03;
const int TILE_GRASS_TO_BRICK = 04;
const int TILE_BRICK_TO_DIRT = 05;
const int TILE_BRICK_TO_GRASS = 06;
const int TILE_NULL = 07;



class Tile
{
public:
  Tile();
  ~Tile();

  void Tile_init( SDL_Renderer*, int, int, int, SDL_Rect[]);
  void Tile_update(double);
  void Tile_render();

  int getType();

private:
  SDL_Renderer* tile_renderer;  // Tile's renderer
  SDL_Texture* tilesheet;       // The tilesheet image
  SDL_Rect tile_img_rect;       // The rect that scouts the tilesheet

  SDL_Rect tileBox; // Collision box of the tile
  int type;         // Tile type (ex: dirt)

};

class Map
{
public:

  Map();
  ~Map();

  void map_init( SDL_Renderer* );
  void read_map();
  void map_update(double);
  void map_render();


private:

  SDL_Renderer* map_renderer;  // Map's renderer

  std::vector<Tile*> TileMap;
  SDL_Rect tileInfo[8];



};
