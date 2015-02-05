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

/*!--------------------------------------------------------------------------
  @brief    Puzzle_Object

  The main puzzle object will be used to represent all puzzle objects.

\----------------------------------------------------------------------------*/
typedef struct _puzzle_object_ {
	int x;					/**< the x position */
	int y;					/**< the y position */
	int rot;				/**< the rotation */
	SSL_Image *image;		/**< the image */
} Puzzle_Object;



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new puzzle Object
  @param	x			x position
  @param	y			y position
  @param	rot			rotation of the object
  @param	image		Image of the object
  @return new Puzzle object else -1 on error

  Creates a enw puzzle object and returns it else -1 on error

\-----------------------------------------------------------------------------*/
Puzzle_Object *puzzle_object_create(int x, int y, int rot, SSL_Image *image);


/*!--------------------------------------------------------------------------
  @brief    Destroys a puzzle object
  @param	object			the object to destroy
  @return Void

  destroys a puzzle object

\-----------------------------------------------------------------------------*/
void puzzle_object_destroy(Puzzle_Object *object);


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
  @brief    Inits the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Inits the puzzle

\-----------------------------------------------------------------------------*/
void puzzle_init(int act, int mission);


/*!--------------------------------------------------------------------------
  @brief    Cleans up the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Cleans up the puzzle

\-----------------------------------------------------------------------------*/
void puzzle_clean_up(int act, int mission);


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
