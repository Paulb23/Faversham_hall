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
#include "../objects/player.h"
#include "map_manager.h"
#include "SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static SSL_Tiled_Map *current_map;	/**< Current tmx map we are on */
static SSL_IniFile *map_ini;		/**< Current ini file for the map */

static int world_offset_x;
static int world_offset_y;

static Player *player;


/*----------------------------------
     Loads the level
 ----------------------------------*/

static void load_level(char *map_name) {
	current_map = load_map(map_name);
	map_ini = load_ini(map_name);
	load_lights(current_map);
	SSL_Tiled_Set_Lighting(current_map, SSL_Color_Create(0, 0, 0, 230));
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
	map_ini = load_ini("start_map");
	int start_x = SSL_IniFile_GetInt(map_ini, "00", "startX", 1);
	int start_y = SSL_IniFile_GetInt(map_ini, "00", "startY", 1);
	load_level(SSL_IniFile_GetString(map_ini, "00", "load", "test_map"));

	player = player_create();
	SSL_Tiled_Add_Light(current_map, player->entity.light);
	entity_set_pos((Entity *)&player->entity, start_x * SSL_Tiled_Get_Tile_Width(current_map), start_y * SSL_Tiled_Get_Tile_Height(current_map));

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
	entity_update_frame((Entity *)&player->entity);

	player_move(player,current_map);


	world_offset_x = -((player->entity.pos.x) - (WINDOW_RES_WIDTH / 2));
	world_offset_y = -((player->entity.pos.y) - (WINDOW_RES_HEIGHT / 2));
}


/*!--------------------------------------------------------------------------
  @brief	Event handler
  @param	event		the event to handle
  @param	uptime		Uptime
  @return 	Void

  Event handler

\-----------------------------------------------------------------------------*/
void game_event_handle(SDL_Event event, int uptime) {
	if(player_check_load(event, player, current_map)) {
		char pos[50] = "";
		sprintf(pos, "%i%i", player->entity.pos.x / SSL_Tiled_Get_Tile_Width(current_map), player->entity.pos.y / SSL_Tiled_Get_Tile_Height(current_map));
		int start_x = SSL_IniFile_GetInt(map_ini, pos , "startX", 1);
		int start_y = SSL_IniFile_GetInt(map_ini, pos, "startY", 1);
		load_level(SSL_IniFile_GetString(map_ini, pos, "load", "test_map"));
		entity_set_pos((Entity *)&player->entity, start_x * SSL_Tiled_Get_Tile_Width(current_map), start_y * SSL_Tiled_Get_Tile_Height(current_map));
		SSL_Tiled_Add_Light(current_map, player->entity.light);
		world_offset_x = 0;
		world_offset_y = 0;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Renders the game
  @return 	Void

  Renders the game.

\-----------------------------------------------------------------------------*/
void game_render() {
	SSL_Tiled_Draw_Map(current_map, world_offset_x, world_offset_y, game_window);
	SSL_Tiled_Draw_Lights(current_map, world_offset_x, world_offset_y, game_window, raytrace);
	SSL_Image_Draw(player->entity.image.image, player->entity.pos.x + world_offset_x, player->entity.pos.y + world_offset_y, 0, player->entity.image.current_frame + (player->entity.image.max_frames * player->entity.image.current_row), 0, game_window);
}
