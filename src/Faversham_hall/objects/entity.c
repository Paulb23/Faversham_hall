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

Entity *create_player() {
	Entity *e = malloc(sizeof(Entity));

	e->pos.x = 16;
	e->pos.y = 16;
	e->pos.w = 16;
	e->pos.h = 16;

	e->image.current_frame = 1;
	e->image.max_frames = 4;
	e->image.next_frame = 0;
	e->image.time_frame = 0;
	e->image.image = SSL_Image_Load("../extras/resources/sprites/test_sprite_ignore_me.png", 16,16,game_window);

	e->light = SSL_Light_Create(16, 16, 0, 0, 7, 0, SSL_Color_Create(255,255,255,255));
	return e;
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
