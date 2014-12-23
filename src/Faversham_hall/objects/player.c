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
#include "entity.h"


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

	player->entity.pos.x = 16;
	player->entity.pos.y = 16;
	player->entity.pos.w = 16;
	player->entity.pos.h = 16;

	player->entity.image.current_frame = 1;
	player->entity.image.current_row = 0;
	player->entity.image.max_frames = 3;
	player->entity.image.next_frame = 0;
	player->entity.image.time_frame = 0;
	player->entity.image.image = SSL_Image_Load("../extras/resources/sprites/test_sprite_ignore_me.png", 16,16,game_window);

	player->entity.light = SSL_Light_Create(16, 16, 0, 0, 4, 0, SSL_Color_Create(255,255,255,255));

	player->destination_x = 0;
	player->destination_y = 0;
	player->last_move_time = 0;
	player->moving = 0;

	return player;
}


/*!--------------------------------------------------------------------------
  @brief	Moves a player
  @param    player		 player to move
  @param    delta		 delta time
  @param    map			 map the player is on
  @return 	Void

  Moves a player

\-----------------------------------------------------------------------------*/
void player_move(Player *player, double delta, SSL_Tiled_Map *map) {
	if (!player->moving && SDL_GetTicks() > player->last_move_time) {
		int layer = SSL_Tiled_Get_LayerIndex(map, "collsion");

		int tile_width = SSL_Tiled_Get_Tile_Width(map);
		int tile_height = SSL_Tiled_Get_Tile_Height(map);
		int player_tile_x = player->entity.pos.x / tile_width;
		int player_tile_y = player->entity.pos.y / tile_height;

		int move_delay = 200;

		int moved = 0;

		if (SSL_Keybord_Keyname_Down("_w") && SSL_Tiled_Get_TileId(map, player_tile_x, player_tile_y - 1, layer) == 0) {
			player->destination_x = player->entity.pos.x;
			player->destination_y = player->entity.pos.y - tile_height;
			player->entity.image.current_row = 0;
			moved = 1;
		} else if (SSL_Keybord_Keyname_Down("_a") && SSL_Tiled_Get_TileId(map, player_tile_x - 1, player_tile_y, layer) == 0) {
			player->destination_x = player->entity.pos.x - tile_width;
			player->destination_y = player->entity.pos.y;
			player->entity.image.current_row = 2;
			moved = 1;
		} else if (SSL_Keybord_Keyname_Down("_s") && SSL_Tiled_Get_TileId(map, player_tile_x, player_tile_y + 1, layer) == 0) {
			player->destination_x = player->entity.pos.x;
			player->destination_y = player->entity.pos.y + tile_height;
			player->entity.image.current_row = 3;
			moved = 1;
		} else if (SSL_Keybord_Keyname_Down("_d") && SSL_Tiled_Get_TileId(map, player_tile_x + 1, player_tile_y, layer) == 0) {
			player->destination_x = player->entity.pos.x + tile_width;
			player->destination_y = player->entity.pos.y;
			player->entity.image.current_row = 1;
			moved = 1;
		} else {
			player->entity.image.current_row = 0;
		}

		if (moved) {
			player->moving = 1;
			player->last_move_time = SDL_GetTicks() + move_delay;
		}
		SSL_Light_SetPos(player->entity.light, player->entity.pos.x ,player->entity.pos.y);
	} else {
		if (player->entity.pos.x == player->destination_x && player->entity.pos.y == player->destination_y) {
			player->moving=0;
			return;
		}

		float vx = player->destination_x - player->entity.pos.x;
		float vy = player->destination_y - player->entity.pos.y;

		player->entity.pos.x += vx;
		player->entity.pos.y += vy;
	}
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
