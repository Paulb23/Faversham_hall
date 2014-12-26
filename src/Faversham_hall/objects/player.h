/*-------------------------------------------------------------------------*/
/**
   @file    player.h
   @author  P. Batty
   @brief   The player object

   This module implements function for manipulating and controlling the
   player.
*/
/*--------------------------------------------------------------------------*/

#ifndef PLAYER_H_
#define PLAYER_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "../../SSL/SSL.h"
#include "entity.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Player

  This object contains information about the player

\----------------------------------------------------------------------------*/
typedef struct _Player_ {
	Entity entity;			/**< The player entity information */
	int moving;				/**< Is the player moving */
	int last_move_time;		/**< Last time the player moved */
	int destination_x;		/**< Destination x to move to */
	int destination_y;		/**< Destination y to move to */
} Player;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Creates a player
  @return 	New player object else return -1

  Creates a player, else -1, destroy with player_destroy();

\-----------------------------------------------------------------------------*/
Player *player_create();


/*!--------------------------------------------------------------------------
  @brief	Moves a player
  @param    player		 player to move
  @param    map			 map the player is on
  @return 	Void

  Moves a player

\-----------------------------------------------------------------------------*/
void player_move(Player *player, SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief	Should we load
  @param    player		 player to check
  @param    map			 map the player is on
  @return 	1 on loading, else 0

  Checks whether the player is on a loading tile, and has started the load.

\-----------------------------------------------------------------------------*/
int player_check_load(SDL_Event event, Player *player, SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief	Destroys a player
  @param    player		 player to destroy
  @return 	Void

  Destroys a player

\-----------------------------------------------------------------------------*/
void player_destroy(Player *player);

#endif
