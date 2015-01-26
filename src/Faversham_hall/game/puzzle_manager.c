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

int valid_clue(int act, int mission) {

	if (act == 1 && mission == 1 && strcmp(game_get_room(), "servants_quarters") == 0) {
		return 1;
	}

	if (act == 2 && mission == 1 && strcmp(game_get_room(), "kitchen") == 0) {
		return 1;
	}

	return 0;
}


void start_clue(int act, int mission) {

	if (act == 1 && mission == 1) {
		found_clue("diary");
	}
	if (act == 2 && mission == 1) {
		found_clue("knifes");
	}

}
