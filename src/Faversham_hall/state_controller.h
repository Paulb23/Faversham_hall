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

/*!--------------------------------------------------------------------------
  @brief    Game_States

  Different states that the game can be in.
	  ASSET_IMAGE - SSL_Image
	  ASSET_SOUND - Mix_Chunk
	  ASSET_FONT  - SSL_Font
	  ASSET_MAP   - SSL_Tiled_Map

\----------------------------------------------------------------------------*/
typedef enum {
	MAIN_MENU,
	GAME_STATE,
	GAME_LOAD_STATE,
	EXIT
} Game_States;

extern Game_States game_state;

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
