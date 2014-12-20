/*-------------------------------------------------------------------------*/
/**
   @file    game.c
   @author  P. Batty
   @brief   Implements a the game loop

   This module implements the game loop
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "game.h"
#include "../config.h"
#include "../state_controller.h"
#include "../window_manager.h"
#include "../objects/entity.h"
#include "map_manager.h"
#include "SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static SSL_Tiled_Map *current_map;		/**< Current tmx map we are on */
static SSL_IniFile *map_ini;		/**< Current ini file for the map */

static int world_offset_x;
static int world_offset_y;

static Entity *player;
int moving;
int dx = 0;
int dy = 0;
int last_time = 0;

static void move_player(double delta) {
	if (!moving && SDL_GetTicks() > last_time) {
		int layer = SSL_Tiled_Get_LayerIndex(current_map, "collsion");

		if (SSL_Keybord_Keyname_Down("_w") && SSL_Tiled_Get_TileId(current_map, (player->pos.x) / 16, (player->pos.y - 16) / 16, layer) == 0) {
			dx = player->pos.x;
			dy = player->pos.y - 16;
			moving = 1;
			last_time = SDL_GetTicks() + 200;
			player->image.current_row = 0;
		} else if (SSL_Keybord_Keyname_Down("_a") && SSL_Tiled_Get_TileId(current_map, (player->pos.x - 16) / 16, (player->pos.y) / 16, layer) == 0) {
			dx = player->pos.x - 16;
			dy = player->pos.y;
			moving = 1;
			last_time = SDL_GetTicks() + 200;
			player->image.current_row = 2;
		} else if (SSL_Keybord_Keyname_Down("_s") && SSL_Tiled_Get_TileId(current_map, (player->pos.x) / 16, (player->pos.y + 16) / 16, layer) == 0) {
			dx = player->pos.x;
			dy = player->pos.y + 16;
			moving = 1;
			last_time = SDL_GetTicks() + 200;
			player->image.current_row = 3;
		} else if (SSL_Keybord_Keyname_Down("_d") && SSL_Tiled_Get_TileId(current_map, (player->pos.x + 16) / 16, (player->pos.y) / 16, layer) == 0) {
			dx = player->pos.x + 16;
			dy = player->pos.y;
			moving = 1;
			last_time = SDL_GetTicks() + 200;
			player->image.current_row = 1;
		} else {
			player->image.current_row = 0;
		}
		SSL_Light_SetPos(player->light, player->pos.x - world_offset_x ,player->pos.y - world_offset_y);
	} else {
		if (player->pos.x == dx && player->pos.y == dy) {
			moving=0;
			return;
		}

		float vx = dx - player->pos.x;
		float vy = dy - player->pos.y;

		player->pos.x += vx;
		player->pos.y += vy;
	}
}

/*----------------------------------
     Loads the level
 ----------------------------------*/

static void load_level(char *map_name) {
	current_map = load_map(map_name);
	map_ini = load_ini(map_name);
	load_lights(current_map);
	SSL_Tiled_Set_Lighting(current_map, SSL_Color_Create(0, 0, 0, 240));
}

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	initialises the game
  @return 	Void

  Starts the game.

\-----------------------------------------------------------------------------*/
void game_init() {
	load_level("test_map");
	player = create_player();
	SSL_Tiled_Add_Light(current_map, player->light);
	moving = 0;
	world_offset_x = 0;
	world_offset_y = 0;
}


/*!--------------------------------------------------------------------------
  @brief	Cleans up the game
  @param	new_state		The state to change to
  @return 	Void

  Cleans up the game

\-----------------------------------------------------------------------------*/
void game_clean_up(Game_States new_state) {

}


/*!--------------------------------------------------------------------------
  @brief	Logic for the game
  @param	delta		Delta time
  @param	uptime		Uptime
  @return 	Void

  Game logic

\-----------------------------------------------------------------------------*/
void game_ticks(double delta, int uptime) {
	move_player(delta);
}


/*!--------------------------------------------------------------------------
  @brief	Event handler
  @param	event		the event to handle
  @param	uptime		Uptime
  @return 	Void

  Event handler

\-----------------------------------------------------------------------------*/
void game_event_handle(SDL_Event event, int uptime) {

}


/*!--------------------------------------------------------------------------
  @brief	Renders the game
  @return 	Void

  Renders the game.

\-----------------------------------------------------------------------------*/
void game_render() {
	SSL_Tiled_Draw_Map(current_map, world_offset_x, world_offset_y, game_window);
	SSL_Tiled_Draw_Lights(current_map, world_offset_x, world_offset_y, game_window, raytrace);
	SSL_Image_Draw(player->image.image, player->pos.x, player->pos.y, 0, player->image.current_frame + (player->image.max_frames * player->image.current_row), 0, game_window);
}
