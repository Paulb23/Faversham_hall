/*-------------------------------------------------------------------------*/
/**
   @file    window_manager.h
   @author  P. Batty
   @brief   Implements a the window manager for the game

   This module implements the window manager for the game, this is where
   the window will be created, destroyed and modified.
*/
/*--------------------------------------------------------------------------*/

#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "../SSL/SSL.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


SSL_Window *game_window;		/**< the game window */


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Creates the window for the game, and sets flags
  @return 	0 on success else -1

  Creates the window for the game and sets the flags according to the
  results of reading the config

\-----------------------------------------------------------------------------*/
int create_window();


/*!--------------------------------------------------------------------------
  @brief	Destroys the window
  @return 	void

  Destroys the window.

\-----------------------------------------------------------------------------*/
void destory_window();

#endif
