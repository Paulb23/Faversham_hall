/*-------------------------------------------------------------------------*/
/**
   @file    game.h
   @author  P. Batty
   @brief   Implements a the game loop

   This module implements the game loop
*/
/*--------------------------------------------------------------------------*/

#ifndef GAME_H_
#define GAME_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "game.h"
#include "../config.h"
#include "../window_manager.h"
#include "../state_controller.h"
#include "SDL2/SDL.h"

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/


/*!--------------------------------------------------------------------------
  @brief	initialises the game
  @param	load	1 to load 0 to not load.
  @return 	Void

  Starts the game.

\-----------------------------------------------------------------------------*/
void game_init(int load);


/*!--------------------------------------------------------------------------
  @brief	Cleans up the game
  @return 	Void

  Cleans up the game

\-----------------------------------------------------------------------------*/
void game_clean_up(Game_States new_state);


/*!--------------------------------------------------------------------------
  @brief	Logic for the game
  @param	delta		Delta time
  @param	uptime		Uptime
  @return 	Void

  Game logic

\-----------------------------------------------------------------------------*/
void game_ticks(double delta, int uptime);


/*!--------------------------------------------------------------------------
  @brief	Event handler
  @param	event		the event to handle
  @param	uptime		Uptime
  @return 	Void

  Event handler

\-----------------------------------------------------------------------------*/
void game_event_handle(SDL_Event event, int uptime);


/*!--------------------------------------------------------------------------
  @brief	Renders the game
  @return 	Void

  Renders the game.

\-----------------------------------------------------------------------------*/
void game_render();


/*!--------------------------------------------------------------------------
  @brief	Gets weatherer are in dialog
  @return 	1 on true else 0

  Gets weatherer are in dialog, returns 1 on true else 0

\-----------------------------------------------------------------------------*/
int game_in_dialog();


/*!--------------------------------------------------------------------------
  @brief	Gets ai name
  @return 	name of the ai, else null

  Gets the name of the ai we are talking to

\-----------------------------------------------------------------------------*/
char *game_get_talking_ai();


/*!--------------------------------------------------------------------------
  @brief	Gets dialog node name
  @return 	name of the dialog node else  null

  Gets the name of the current dialog node in conversation else null

\-----------------------------------------------------------------------------*/
char *game_get_dialog_node_name();


/*!--------------------------------------------------------------------------
  @brief	Gets room currently in
  @return 	name of the room the player is in

  Gets the name of the room the player is currently in

\-----------------------------------------------------------------------------*/
char *game_get_room();

/*!--------------------------------------------------------------------------
  @brief	Locks the dialog
  @return 	Void

  Stops the player from the leaving the dialog

\-----------------------------------------------------------------------------*/
void lock_dialog();


/*!--------------------------------------------------------------------------
  @brief	Unlocks the dialog
  @return 	Void

  Allows the player from the leaving the dialog

\-----------------------------------------------------------------------------*/
void unlock_dialog();


/*!--------------------------------------------------------------------------
  @brief	Starts a puzzle sequence
  @return 	Void

  Starts a puzzle sequence.

\-----------------------------------------------------------------------------*/
void start_puzzle();

#endif
