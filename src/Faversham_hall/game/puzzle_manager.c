/*-------------------------------------------------------------------------*/
/**
   @file    puzzle_manager.c
   @author  P. Batty
   @brief   ...

   This module implements...

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "puzzle_manager.h"
#include "mission_manager.h"
#include "game.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Validates the clue
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return 1 if valued else 0

  Checks if the clue can be access at the current point. return1 if valid else 0

\-----------------------------------------------------------------------------*/
int valid_clue(int act, int mission) {

	if (act == 1 && mission == 1 && strcmp(game_get_room(), "servants_quarters") == 0) {
		return 1;
	}

	if (act == 2 && mission == 1 && strcmp(game_get_room(), "kitchen") == 0) {
		return 1;
	}

	return 0;
}


/*!--------------------------------------------------------------------------
  @brief    Starts the clue
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Starts the clue / puzzle and passes it on to the mission manager

\-----------------------------------------------------------------------------*/
void start_clue(int act, int mission) {

	if (act == 1 && mission == 1) {
		found_clue("diary");
	}
	if (act == 2 && mission == 1) {
		found_clue("knifes");
	}

}
