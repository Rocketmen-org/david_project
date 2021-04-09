#include "MapManager.h"

Tile::Tile()
{}
Tile::~Tile()
{}
Map::Map()
{}
Map::~Map()
{}



void Tile::Tile_init( SDL_Renderer* ren, int x, int y, int tileType, SDL_Rect tileInfo[] )
{

  tile_renderer = ren;

  // Give the tile the tilesheet
  SDL_Surface* temp = IMG_Load("tilesheet.png");
  tilesheet = SDL_CreateTextureFromSurface(ren, temp);
  SDL_FreeSurface(temp);

  tileBox.x = x;
  tileBox.y = y;
  tileBox.w = TILE_WIDTH;
  tileBox.h = TILE_HEIGHT;

  type = tileType;

  tile_img_rect.x = tileInfo[type].x;
  tile_img_rect.y = tileInfo[type].y;
  tile_img_rect.w = TILE_WIDTH;
  tile_img_rect.h = TILE_HEIGHT;
}

void Tile::Tile_update( double x_vel )
{

  tileBox.x += x_vel;

}

void Tile::Tile_render()
{

  // Check to see if the tile's rect collides with the screen view
  bool x_collision = false;
  bool y_collision = false;

  // Check for X collision
  if( tileBox.x > 0 || tileBox.x + TILE_WIDTH < SCREEN_WIDTH )
  {
    x_collision = true;
  }
  if( tileBox.y > 0 || tileBox.y + TILE_HEIGHT < SCREEN_HEIGHT )
  {
    y_collision = true;
  }

  if( x_collision && y_collision )
  {
    // If there is a collision, then render
    SDL_RenderCopy( tile_renderer, tilesheet, &tile_img_rect, &tileBox );
  }

}

int Tile::getType()
{
  return type;
}


void Map::map_init( SDL_Renderer* ren )
{

  map_renderer = ren;
  // Hardcoding this because I tried for days on end trying to figure out how
  // not to but im tired and the project is already late so whatever
  // if you want me to do it different please tell me how so I can finally
  // start getting creative with this stuff instead of getting stuck

  // but anyway yes i agree this is an ugly way of doing it

  tileInfo[TILE_DIRT].x = 0;
  tileInfo[TILE_DIRT].y = 0;
  tileInfo[TILE_DIRT].w = TILE_WIDTH;
  tileInfo[TILE_DIRT].h = TILE_HEIGHT;

  tileInfo[TILE_GRASS].x = 200;
  tileInfo[TILE_GRASS].y = 00;
  tileInfo[TILE_GRASS].w = TILE_WIDTH;
  tileInfo[TILE_GRASS].h = TILE_HEIGHT;

  tileInfo[TILE_BRICK].x = 300;
  tileInfo[TILE_BRICK].y = 0;
  tileInfo[TILE_BRICK].w = TILE_WIDTH;
  tileInfo[TILE_BRICK].h = TILE_HEIGHT;

  tileInfo[TILE_DIRT_TO_BRICK].x = 0;
  tileInfo[TILE_DIRT_TO_BRICK].y = 100;
  tileInfo[TILE_DIRT_TO_BRICK].w = TILE_WIDTH;
  tileInfo[TILE_DIRT_TO_BRICK].h = TILE_HEIGHT;

  tileInfo[TILE_BRICK_TO_DIRT].x = 100;
  tileInfo[TILE_BRICK_TO_DIRT].y = 100;
  tileInfo[TILE_BRICK_TO_DIRT].w = TILE_WIDTH;
  tileInfo[TILE_BRICK_TO_DIRT].h = TILE_HEIGHT;

  tileInfo[TILE_GRASS_TO_BRICK].x = 200;
  tileInfo[TILE_GRASS_TO_BRICK].y = 100;
  tileInfo[TILE_GRASS_TO_BRICK].w = TILE_WIDTH;
  tileInfo[TILE_GRASS_TO_BRICK].h = TILE_HEIGHT;

  tileInfo[TILE_BRICK_TO_GRASS].x = 300;
  tileInfo[TILE_BRICK_TO_GRASS].y = 100;
  tileInfo[TILE_BRICK_TO_GRASS].w = TILE_WIDTH;
  tileInfo[TILE_BRICK_TO_GRASS].h = TILE_HEIGHT;

  tileInfo[TILE_NULL].x = 100;
  tileInfo[TILE_NULL].y = 0;
  tileInfo[TILE_NULL].w = TILE_WIDTH;
  tileInfo[TILE_NULL].h = TILE_HEIGHT;

}

void Map::read_map()
{

  int x = 0;
  int y = 0;

  std::ifstream map( "map1.txt" );

  if( map.fail() )
  {
    std::cout << "Couldn't open the map?\n" ;
  }
  else
  {
    for( int i = 0; i < TOTAL_TILES; ++i )
    {

      int tileType = -1;
      Tile* tempTile = new Tile();

      // Read in the tile type from map file
      map >> tileType;

      // Create a new tile and put it in the map
      tempTile->Tile_init( map_renderer, x, y , tileType, tileInfo );
      TileMap.push_back( tempTile );

      // Adjust the coordinates of the tile
      x += TILE_WIDTH;
      if( x >= LEVEL_WIDTH )
      {
        x = 0;
        y += TILE_HEIGHT;
      }

    }
  }


}

void Map::map_update( double x_vel )
{
  for( int i = 0; i < TOTAL_TILES; i++ )
  {
    TileMap[i]->Tile_update(x_vel);
  }
}

void Map::map_render()
{
  for( int i = 0; i < TOTAL_TILES; i++ )
  {
    TileMap[i]->Tile_render();
  }
}
