/*-------------------------------------------------------------------------*/
/**
   @file    mission_manager.h
   @author  P. Batty
   @brief   Manages the mission and acts

   This module implements the system to manage and control the different
   scenes and missions in the game.

*/
/*--------------------------------------------------------------------------*/

#ifndef MISSION_MANAGER_H_
#define MISSION_MANAGER_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	inits the mission manager
  @return 	Void

  Inits the mission manager

\-----------------------------------------------------------------------------*/
void act_init();


/*!--------------------------------------------------------------------------
  @brief	Checks if a room is locked
  @param	room		Name of the room to check
  @return 	1 on true else 0

  Checks to see if the room is look and returns 1 if locked else 0

\-----------------------------------------------------------------------------*/
int is_room_locked(char *room);


/*!--------------------------------------------------------------------------
  @brief	Checks if a npc is locked
  @param	npc 		Name of the npc to check
  @return 	1 on true else 0

  Checks if the npc is locked and returns 1 if locked else 0

\-----------------------------------------------------------------------------*/
int is_npc_locked(char *npc);


/*!--------------------------------------------------------------------------
  @brief	Updates the act
  @return 	Void

  Updates the act

\-----------------------------------------------------------------------------*/
void update_act();


/*!--------------------------------------------------------------------------
  @brief	Draws the act
  @return 	Void

  Draws the act

\-----------------------------------------------------------------------------*/
void draw_act();


/*!--------------------------------------------------------------------------
  @brief	Gets the current act
  @return 	current act number

  Gets the current act

\-----------------------------------------------------------------------------*/
int get_current_act();


/*!--------------------------------------------------------------------------
  @brief	Gets the current mission
  @return 	current mission number

  Gets the current mission

\-----------------------------------------------------------------------------*/
int get_current_mission();

#endif