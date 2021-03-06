/*-------------------------------------------------------------------------*/
/**
   @file    player.c
   @author  P. Batty
   @brief   The player object

   This module implements function for manipulating and controlling the
   player.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "player.h"
#include "../../SSL/SSL.h"
#include "../window_manager.h"
#include "../asset_manager.h"
#include "../config.h"
#include "entity.h"
#include "ai.h"
#include "math.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Creates a player
  @return 	New player object else return -1

  Creates a player, else -1, destroy with player_destroy();

\-----------------------------------------------------------------------------*/
Player *player_create() {
	Player *player = malloc(sizeof(Player));

	player->entity.pos.x = 0;
	player->entity.pos.y = 0;
	player->entity.pos.w = 16;
	player->entity.pos.h = 16;

	player->entity.image.current_frame = 1;
	player->entity.image.current_row = 0;
	player->entity.image.max_frames = 5;
	player->entity.image.next_frame = 0;
	player->entity.image.time_frame = 150;
	player->entity.image.image = SSL_Image_Load("../extras/resources/sprites/Detective.png", 16,16,game_window);

	player->entity.light = SSL_Light_Create(16, 16, 0, 0, 6, 0, SSL_Color_Create(255,255,255,255));

	player->destination_x = 0;
	player->destination_y = 0;
	player->last_move_time = 0;
	player->moving = 0;

	return player;
}


/*!--------------------------------------------------------------------------
  @brief	Moves a player
  @param    player		 player to move
  @param    map			 map the player is on
  @return 	Void

  Moves a player

\-----------------------------------------------------------------------------*/
void player_move(Player *player, SSL_Tiled_Map *map) {
	if (!player->moving && SDL_GetTicks() > player->last_move_time) {	// check we can move
		int layer = SSL_Tiled_Get_LayerIndex(map, "collsion");			// get the collision layer

		int tile_width = SSL_Tiled_Get_Tile_Width(map);					// get tile size
		int tile_height = SSL_Tiled_Get_Tile_Height(map);
		int player_tile_x = player->entity.pos.x / tile_width;			// get player tile number
		int player_tile_y = player->entity.pos.y / tile_height;

		int move_delay = 200;											// default delay between moves

		int moved = 0;
																		// up movment
		if (SSL_Keybord_Keyname_Down(UP_KEY) && SSL_Tiled_Get_TileId(map, player_tile_x, player_tile_y - 1, layer) == 0) {
			player->destination_x = player->entity.pos.x;
			player->destination_y = player->entity.pos.y - tile_height;
			player->entity.image.current_row = 2;
			moved = 1;													// left movment
		} else if (SSL_Keybord_Keyname_Down(LEFT_KEY) && SSL_Tiled_Get_TileId(map, player_tile_x - 1, player_tile_y, layer) == 0) {
			player->destination_x = player->entity.pos.x - tile_width;
			player->destination_y = player->entity.pos.y;
			player->entity.image.current_row = 1;
			moved = 1;													// down movment
		} else if (SSL_Keybord_Keyname_Down(DOWN_KEY) && SSL_Tiled_Get_TileId(map, player_tile_x, player_tile_y + 1, layer) == 0) {
			player->destination_x = player->entity.pos.x;
			player->destination_y = player->entity.pos.y + tile_height;
			player->entity.image.current_row = 0;
			moved = 1;													// right movment
		} else if (SSL_Keybord_Keyname_Down(RIGHT_KEY) && SSL_Tiled_Get_TileId(map, player_tile_x + 1, player_tile_y, layer) == 0) {
			player->destination_x = player->entity.pos.x + tile_width;
			player->destination_y = player->entity.pos.y;
			player->entity.image.current_row = 3;
			moved = 1;
		} else {														// no moment, set to idle
			player->entity.image.current_row = 5;
		}

		if (moved) {													// if we moved set flag and calculate next move time.
			player->moving = 1;
			player->last_move_time = SDL_GetTicks() + move_delay;
		}
		SSL_Light_SetPos(player->entity.light, player->entity.pos.x ,player->entity.pos.y);							// update the light
	} else {																										// else we are moving
		if (player->entity.pos.x == player->destination_x && player->entity.pos.y == player->destination_y) {		// check we are not at destination
			player->moving=0;
			return;
		}

		float vx = player->destination_x - player->entity.pos.x;													// else calculate next move
		float vy = player->destination_y - player->entity.pos.y;

		player->entity.pos.x += vx;																					// set position
		player->entity.pos.y += vy;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Should we load
  @param	event 		 the event queue
  @param    player		 player to check
  @param    map			 map the player is on
  @return 	1 on loading, else 0

  Checks whether the player is on a loading tile, and has started the load.

\-----------------------------------------------------------------------------*/
int player_check_load(SDL_Event event, Player *player, SSL_Tiled_Map *map) {
	int layer = SSL_Tiled_Get_LayerIndex(map, "other");					// get the loading tile layer
	if (SSL_Tiled_Get_TileId(map, entity_get_tile_x((Entity *)&player->entity, map), entity_get_tile_y((Entity *)&player->entity, map), layer) == 1) {
		if (SSL_Keybord_Keyname_Pressed(INTERACT_KEY, event)) {			// check the player wants to load
			return 1;
		}
	}
 return 0;
}


/*!--------------------------------------------------------------------------
  @brief	Should we start conversation
  @param	event 		 the event queue
  @param    player		 player to check
  @param    map			 map the player is on
  @return 	1 on loading, else 0

  Checks whether the player is on a conversation tile, and has started the conversation.

\-----------------------------------------------------------------------------*/
int player_character_interaction_check(SDL_Event event, Player *player, SSL_Tiled_Map *map) {
	int layer = SSL_Tiled_Get_LayerIndex(map, "other");					// get the loading tile layer
	if (SSL_Tiled_Get_TileId(map, entity_get_tile_x((Entity *)&player->entity, map), entity_get_tile_y((Entity *)&player->entity, map), layer) == 4) {
		if (SSL_Keybord_Keyname_Pressed(INTERACT_KEY, event)) {			// check the player wants to load
			return 1;
		}
	}
 return 0;
}


/*!--------------------------------------------------------------------------
  @brief	Should we start the clue / puzzle
  @param	event 		 the event queue
  @param    player		 player to check
  @param    map			 map the player is on
  @return 	1 on loading, else 0

  Checks whether the player is on a clue tile, and has started the clue interaction.

\-----------------------------------------------------------------------------*/
int player_clue_interaction_check(SDL_Event event, Player *player, SSL_Tiled_Map *map) {
	int layer = SSL_Tiled_Get_LayerIndex(map, "other");					// get the clue tile layer
	if (SSL_Tiled_Get_TileId(map, entity_get_tile_x((Entity *)&player->entity, map), entity_get_tile_y((Entity *)&player->entity, map), layer) == 3) {
		if (SSL_Keybord_Keyname_Pressed(INTERACT_KEY, event)) {			// check the player wants to load
			return 1;
		}
	}
 return 0;
}


/*!--------------------------------------------------------------------------
  @brief	Gets the name of the closest ai
  @param    player		 player to check
  @param    list		 The list of ai
  @return 	Name of the closet ai

  Gets the name of the closest ai and returns it

\-----------------------------------------------------------------------------*/
char *get_closest_ai_name(Player *player, SSL_List *list) {
	int i;
	AI *ai;
	int dist = 10000;
	for (i = 0; i < SSL_List_Size(list); i++) {
		AI *tmp = (AI *)SSL_List_Get(list, i);
		int xd = player->entity.pos.x - tmp->entity.pos.x;
		int yd = player->entity.pos.y - tmp->entity.pos.y;
		int d =  sqrt(xd*xd + yd*yd);
		if (d < dist) {
			dist = d;
			ai = tmp;
		}
	}

	return ai->name;
}


/*!--------------------------------------------------------------------------
  @brief	Destroys a player
  @param    player		 player to destroy
  @return 	Void

  Destroys a player

\-----------------------------------------------------------------------------*/
void player_destroy(Player *player) {
	SSL_Image_Destroy(player->entity.image.image);
	free(player);
}
