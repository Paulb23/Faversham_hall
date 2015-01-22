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
  @return 	Void

  Starts the game.

\-----------------------------------------------------------------------------*/
void game_init();


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

#endif
