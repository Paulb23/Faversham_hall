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

void dialog_init();
void dialog_clean_up();
void start_dialog(char *other, int act);
int update_dialog(SDL_Event event);
void render_dialog();
char *get_node_name();

#endif
