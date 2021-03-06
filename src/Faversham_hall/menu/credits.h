/*-------------------------------------------------------------------------*/
/**
   @file    credits.h
   @author  P. Batty
   @brief   ...

   This module implements...

*/
/*--------------------------------------------------------------------------*/

#ifndef CREDITS_H_
#define CREDITS_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	initialises the credits
  @return 	Void

  inits the main menu.

\-----------------------------------------------------------------------------*/
void credits_init();


/*!--------------------------------------------------------------------------
  @brief	Cleans up the credits
  @return 	Void

  Cleans up the credits

\-----------------------------------------------------------------------------*/
void credits_clean_up();


/*!--------------------------------------------------------------------------
  @brief	Logic for the credits
  @return 	Void

  Credits logic

\-----------------------------------------------------------------------------*/
void credits_ticks();


/*!--------------------------------------------------------------------------
  @brief	Event handler
  @param	event		the event to handle
  @return 	Void

  Event handler

\-----------------------------------------------------------------------------*/
void credits_handeler(SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief	Renders the credits
  @return 	Void

  Renders the credits.

\-----------------------------------------------------------------------------*/
void credits_renderer();

#endif
