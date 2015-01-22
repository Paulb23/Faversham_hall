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

void act_init();
int is_room_locked(char *room);
int is_npc_locked(char *npc);
void update_act();
void draw_act();

#endif
