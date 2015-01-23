/*-------------------------------------------------------------------------*/
/**
   @file    AI.c
   @author  P. Batty
   @brief   The player object

   This module implements function for manipulating and controlling the
   ai.
*/
/*--------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "../../SSL/SSL.h"
#include "../window_manager.h"
#include "entity.h"
#include "ai.h"


/*---------------------------------------------------------------------------
                                Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Creates a ai
  @param    name		 name of the AI
  @return 	New Ai object else -1

  Creates a ai, and returns it else -1 on error

\-----------------------------------------------------------------------------*/
AI *ai_create(char *name) {
	AI *ai = malloc(sizeof(AI));

	ai->entity.pos.x = 0;
	ai->entity.pos.y = 0;
	ai->entity.pos.w = 16;
	ai->entity.pos.h = 16;

	ai->entity.image.current_frame = 1;
	ai->entity.image.current_row = 0;
	ai->entity.image.max_frames = 3;
	ai->entity.image.next_frame = 0;
	ai->entity.image.time_frame = 150;

	ai->entity.light = SSL_Light_Create(16, 16, 0, 0, 6, 0, SSL_Color_Create(255,255,255,255));
	ai->entity.image.image = SSL_Image_Load("../extras/resources/sprites/test_sprite_ignore_me.png", 16,16,game_window);

	ai->name = name;

	return ai;
}


/*!--------------------------------------------------------------------------
  @brief	Destroys a ai
  @param    ai			 ai to destroy
  @return 	Void

  Destroys a ai

\-----------------------------------------------------------------------------*/
void ai_destroy(AI *ai) {
	SSL_Image_Destroy(ai->entity.image.image);
	free(ai);
}

