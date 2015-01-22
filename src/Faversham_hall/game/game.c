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
#include "../objects/ai.h"
#include "map_manager.h"
#include "mission_manager.h"
#include "../asset_manager.h"
#include "dialogue_parser.h"
#include "SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static char *current_map_name = "";	/**< Name of the current map we are on*/

static SSL_Tiled_Map *current_map;	/**< Current tmx map we are on */
static SSL_IniFile *map_ini;		/**< Current ini file for the map */

static int world_offset_x;			/**< X offset of the world */
static int world_offset_y;			/**< Y offset of the world */

static Player *player;				/**< The player */
static SSL_List *ai;				/**< The Ai list */

int in_dialog;						/**< Are we in dialogue */
int locked_room;					/**< is the room we are tying to load locked */


/*----------------------------------
     Loads the level
 ----------------------------------*/

static void load_level(char *map_name) {
	current_map = load_map(map_name); // load the map and ini files
	map_ini = load_ini(map_name);
	current_map_name = map_name;	  // update the map name
	load_lights(current_map);		  // set up lighting
	SSL_Tiled_Set_Lighting(current_map, SSL_Color_Create(0, 0, 0, 230));

	// destory the old list
	if (ai) {
		SSL_List_Destroy(ai);
	}
	ai = SSL_List_Create();			// set up ai
	load_ai(current_map, ai);
	load_servant(current_map, ai);
}


/*----------------------------------
     Loads the next level
 ----------------------------------*/

static void load_next_level() {
	char pos[50] = "";																		// combine the xy coordinates of the player
	sprintf(pos, "%i%i", player->entity.pos.x / SSL_Tiled_Get_Tile_Width(current_map), player->entity.pos.y / SSL_Tiled_Get_Tile_Height(current_map));
	int start_x = SSL_IniFile_GetInt(map_ini, pos , "startX", 1);							// read the current map ini, for the next map name,
	int start_y = SSL_IniFile_GetInt(map_ini, pos, "startY", 1);							// and starting x, y coordinates

	if (is_room_locked(SSL_IniFile_GetString(map_ini, pos, "load", "test_map"))) {
		locked_room = 1;
		return;
	}

	load_level(SSL_IniFile_GetString(map_ini, pos, "load", "test_map"));					// load the level

																							// set up the player for the new map
	entity_set_pos((Entity *)&player->entity, start_x * SSL_Tiled_Get_Tile_Width(current_map), start_y * SSL_Tiled_Get_Tile_Height(current_map));
	player->destination_x = start_x * SSL_Tiled_Get_Tile_Width(current_map);
	player->destination_y = start_y * SSL_Tiled_Get_Tile_Width(current_map);
	SSL_Tiled_Add_Light(current_map, player->entity.light);
	in_dialog = 0;
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	initialises the game
  @return 	Voids

  Starts the game.

\-----------------------------------------------------------------------------*/
void game_init() {
	dialog_init();	// set up the dialog

	map_ini = load_ini("start_map");	// get the start_map ini and read it
	int start_x = SSL_IniFile_GetInt(map_ini, "00", "startX", 1);
	int start_y = SSL_IniFile_GetInt(map_ini, "00", "startY", 1);
										// load the map stored in the start_map ini
	load_level(SSL_IniFile_GetString(map_ini, "00", "load", "test_map"));

	player = player_create();			// create and load the player
	SSL_Tiled_Add_Light(current_map, player->entity.light);
	entity_set_pos((Entity *)&player->entity, start_x * SSL_Tiled_Get_Tile_Width(current_map), start_y * SSL_Tiled_Get_Tile_Height(current_map));

	world_offset_x = 0;
	world_offset_y = 0;
	locked_room = 0;

	// set up the mssion counter
	act_init();
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

	// update animations
	entity_update_frame((Entity *)&player->entity);
	int i;
	for (i = 0; i < SSL_List_Size(ai); i++) {
		AI *character = (AI *)SSL_List_Get(ai, i);
		entity_update_frame((Entity *)&character->entity);
	}

	// handle player movment
	player_move(player,current_map);

	// update camrea offset
	world_offset_x = -((player->entity.pos.x) - (WINDOW_RES_WIDTH / 2));
	world_offset_y = -((player->entity.pos.y) - (WINDOW_RES_HEIGHT / 2));

	// exit dialog on player move
	if (player->moving) {
		in_dialog = 0;
		locked_room = 0;
	}

	// update the mission
	update_act();
}


/*!--------------------------------------------------------------------------
  @brief	Event handler
  @param	event		the event to handle
  @param	uptime		Uptime
  @return 	Void

  Event handler

\-----------------------------------------------------------------------------*/
void game_event_handle(SDL_Event event, int uptime) {

	// if we are not in dialog
	if (!in_dialog) {

		/* check for loading and if so
		 * load the map and set up the player
		 */
		if(player_check_load(event, player, current_map)) {
			load_next_level();
		}

		/* check for character interaction and if so
		 * start the conversation
		 */
		if(player_character_interaction_check(event, player, current_map)) {
			start_dialog(get_closest_ai_name(player, ai), 1);
			in_dialog = 1;
		}
	} else {
		// else update the dialog
		in_dialog = update_dialog(event);
	}
}


/*!--------------------------------------------------------------------------
  @brief	Renders the game
  @return 	Void

  Renders the game.

\-----------------------------------------------------------------------------*/
void game_render() {

	// draw the world
	SSL_Tiled_Draw_Map(current_map, world_offset_x, world_offset_y, game_window);
	SSL_Tiled_Draw_Lights(current_map, world_offset_x, world_offset_y, game_window, raytrace);

	// draw the player
	SSL_Image_Draw(player->entity.image.image, player->entity.pos.x + world_offset_x, player->entity.pos.y + world_offset_y, 0, player->entity.image.current_frame + (player->entity.image.max_frames * player->entity.image.current_row), 0, game_window);

	// draw the ai
	int i;
	for (i = 0; i < SSL_List_Size(ai); i++) {
		AI *character = (AI *)SSL_List_Get(ai, i);
		SSL_Image_Draw(character->entity.image.image, character->entity.pos.x + world_offset_x, character->entity.pos.y + world_offset_y, 0, character->entity.image.current_frame + (character->entity.image.max_frames * character->entity.image.current_row), 0, game_window);
	}

	//if we are in dialog draw it
	if (in_dialog) {
		render_dialog();
	} else {

		// else check and draw info about available interactions
		int layer = SSL_Tiled_Get_LayerIndex(current_map, "other");					// get the loading tile layer
		if (SSL_Tiled_Get_TileId(current_map, entity_get_tile_x((Entity *)&player->entity, current_map), entity_get_tile_y((Entity *)&player->entity, current_map), layer) == 1) {
			SSL_Font_Draw(10, 25, 0 ,SDL_FLIP_NONE, "Press E to load", (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
		}
		if (SSL_Tiled_Get_TileId(current_map, entity_get_tile_x((Entity *)&player->entity, current_map), entity_get_tile_y((Entity *)&player->entity, current_map), layer) == 4) {
			SSL_Font_Draw(10, 25, 0 ,SDL_FLIP_NONE, "Press E to Talk", (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
		}

		// let them know the room is locked
		if (locked_room) {
			SSL_Font_Draw(10, 40, 0 ,SDL_FLIP_NONE, "Room Locked!", (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
		}

		// draw the mission info
		draw_act();
	}
}


/*!--------------------------------------------------------------------------
  @brief	Gets weatherer are in dialog
  @return 	1 on true else 0

  Gets weatherer are in dialog, returns 1 on true else 0

\-----------------------------------------------------------------------------*/
int game_in_dialog() {
	return in_dialog;
}


/*!--------------------------------------------------------------------------
  @brief	Gets ai name
  @return 	name of the ai, else null

  Gets the name of the ai we are talking to

\-----------------------------------------------------------------------------*/
char *game_get_talking_ai() {
	if (in_dialog) {
		return get_closest_ai_name(player, ai);
	} else {
		return NULL;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Gets dialog node name
  @return 	name of the dialog node else  null

  Gets the name of the current dialog node in conversation else null

\-----------------------------------------------------------------------------*/
char *game_get_dialog_node_name() {
	if (in_dialog) {
		return get_node_name();
	} else {
		return NULL;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Gets room currently in
  @return 	name of the room the player is in

  Gets the name of the room the player is currently in

\-----------------------------------------------------------------------------*/
char *game_get_room() {
	return current_map_name;
}
