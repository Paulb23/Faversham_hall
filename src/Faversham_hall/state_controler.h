/*-------------------------------------------------------------------------*/
/**
   @file    state_controler.h
   @author  P. Batty
   @brief   Implements a the game state controller

   This module implements the game state controller and will control
   the state of the game.
*/
/*--------------------------------------------------------------------------*/

#ifndef STATE_CONTROLER_H_
#define STATE_CONTROLER_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

typedef enum {
	MAIN_MENU,
	GAME_STATE,
	EXIT
} Game_States;

Game_States game_state;

/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Starts the game
  @return 	Void

  Starts the game.

\-----------------------------------------------------------------------------*/
void start_game();


/*!--------------------------------------------------------------------------
  @brief	Switches the game state
  @param	new_state		The state to switch to
  @return 	Void

  Switches the game state

\-----------------------------------------------------------------------------*/
void switch_state(Game_States new_state);

#endif
