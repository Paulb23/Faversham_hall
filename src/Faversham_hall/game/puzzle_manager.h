/*-------------------------------------------------------------------------*/
/**
   @file    puzzle_manager.h
   @author  P. Batty
   @brief   Manages puzzle and clues

   This module implements the games way to manage clues and puzzles.

*/
/*--------------------------------------------------------------------------*/

#ifndef PUZZLE_MANAGER_H_
#define PUZZLE_MANAGER_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "../window_manager.h"

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Validates the clue
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return 1 if valued else 0

  Checks if the clue can be access at the current point. return1 if valid else 0

\-----------------------------------------------------------------------------*/
int valid_clue(int act, int mission);


/*!--------------------------------------------------------------------------
  @brief    Starts the clue
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Starts the clue / puzzle and passes it on to the mission manager

\-----------------------------------------------------------------------------*/
void start_clue(int act, int mission);


/*!--------------------------------------------------------------------------
  @brief    Updates the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Updates the puzzle
\-----------------------------------------------------------------------------*/
void puzzle_update(int act, int mission);


/*!--------------------------------------------------------------------------
  @brief    Handles the puzzle events
  @param	event		the event queue
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return 1 if failed else 0 on completion

  Updates the puzzle events
\-----------------------------------------------------------------------------*/
int puzzle_update_events(SDL_Event event, int act, int mission);


/*!--------------------------------------------------------------------------
  @brief    Renders the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Renders the puzzle
\-----------------------------------------------------------------------------*/
void puzzle_render(int act, int mission);

#endif
