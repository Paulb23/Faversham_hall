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
  @brief	Sets the position of the entity
  @param    entity		 entity to update
  @param	x			 New x position of the entity
  @param	y			 New y position of the entity
  @return 	Void

  Updates the current animation frame for the entity

\-----------------------------------------------------------------------------*/
void entity_set_pos(Entity *entity, int x, int y) {
	entity->pos.x = x;
	entity->pos.y = y;
}


/*!--------------------------------------------------------------------------
  @brief	Gets the tile x that the entity is on
  @param    entity		 entity to get the tile of
  @param	map			 map to use
  @return 	Current x tile of the entity

  Gets the tile x that the entity is on

\-----------------------------------------------------------------------------*/
int entity_get_tile_x(Entity *entity, SSL_Tiled_Map *map) {
	return entity->pos.x / SSL_Tiled_Get_Tile_Width(map);
}


/*!--------------------------------------------------------------------------
  @brief	Gets the tile y that the entity is on
  @param    entity		 entity to get the tile of
  @param	map			 map to use
  @return 	Current x tile of the entity

  Gets the tile y that the entity is on

\-----------------------------------------------------------------------------*/
int entity_get_tile_y(Entity *entity, SSL_Tiled_Map *map) {
	return entity->pos.y / SSL_Tiled_Get_Tile_Height(map);
}


/*!--------------------------------------------------------------------------
  @brief	Updates the current animation frame
  @param    entity		 entity to update
  @return 	Void

  Updates the current animation frame for the entity

\-----------------------------------------------------------------------------*/
void entity_update_frame(Entity *entity) {
	if (SDL_GetTicks() > entity->image.next_frame) {					// check it time to update
		entity->image.current_frame += 1;								// goto next frame

		if (entity->image.current_frame > entity->image.max_frames) {	// if it's greater the max frames
			entity->image.current_frame = 1;							// set it to loop
		}
																		// calculate the frame update time
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
