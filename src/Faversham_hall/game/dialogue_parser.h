/*-------------------------------------------------------------------------*/
/**
   @file    dialogue_parser.h
   @author  P. Batty
   @brief   The dialog parser

   This module implements The dialog parser

*/
/*--------------------------------------------------------------------------*/

#ifndef DIALOGUE_PARSER_H_
#define DIALOGUE_PARSER_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2\SDL.h"

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Inits the dialog parser
  @return 	Void

  Inits the dialog parser.

\-----------------------------------------------------------------------------*/
void dialog_init();


/*!--------------------------------------------------------------------------
  @brief	Cleans up the dialog parser
  @return 	Void

  Cleans up the dialog parser.

\-----------------------------------------------------------------------------*/
void dialog_clean_up();


/*!--------------------------------------------------------------------------
  @brief	Starts the dialog
  @param	other		The npc name
  @param	act			The act number
  @return 	Void

  Cleans up the dialog parser.

\-----------------------------------------------------------------------------*/
void start_dialog(char *other, int act);


/*!--------------------------------------------------------------------------
  @brief	Dialog event handler
  @param	event		The event queue
  @return 	1 if the Dialog is ended else 0

  Handles events for the dialog parser. returns 1 if the Dialog is ended else 0

\-----------------------------------------------------------------------------*/
int update_dialog(SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief	Draws the dialog
  @return 	Void

  Draws the dialog

\-----------------------------------------------------------------------------*/
void render_dialog();


/*!--------------------------------------------------------------------------
  @brief	Gets the current dialog node
  @return 	name of the current dialog node

  Gets the current dialog node

\-----------------------------------------------------------------------------*/
char *get_node_name();

#endif
