/*-------------------------------------------------------------------------*/
/**
   @file    entity.c
   @author  P. Batty
   @brief   Implements a the entity system for the game

   This module implements the entity system for the game, and sprite
   system.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "entity.h"
#include "../window_manager.h"
#include "../../SSL/SSL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Updates the current animation frame
  @param    entity		 entity to update
  @return 	Void

  Updates the current animation frame for the entity

\-----------------------------------------------------------------------------*/
void entity_update_frame(Entity *entity) {
	if (SDL_GetTicks() > entity->image.next_frame) {
		entity->image.current_frame += 1;

		if (entity->image.current_frame > entity->image.max_frames) {
			entity->image.current_frame = 1;
		}

		entity->image.next_frame = SDL_GetTicks() + entity->image.time_frame;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Destroys a entity
  @param    entity		 entity to destroy
  @return 	Void

  Destroys a entity

\-----------------------------------------------------------------------------*/
void entity_destroy(Entity *entity) {
	SSL_Image_Destroy(entity->image.image);
	free(entity);
}
