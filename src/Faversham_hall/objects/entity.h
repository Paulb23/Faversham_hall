/*-------------------------------------------------------------------------*/
/**
   @file    entity.h
   @author  P. Batty
   @brief   Implements a the entity system for the game

   This module implements the entity system for the game, and sprite
   system.
*/
/*--------------------------------------------------------------------------*/

#ifndef ENTITY_H_
#define ENTITY_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "../../SSL/SSL.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Entity_Pos

  This object contains information the entities position

\----------------------------------------------------------------------------*/
typedef struct _entity_pos_ {
	int x;						/**< X position of the entity */
	int y;						/**< Y position of the entity */
	int w;						/**< Width of the entity */
	int h;						/**< Height of the entity */
} Entity_pos;


/*!--------------------------------------------------------------------------
  @brief    Entity_image

  This object contains information the entities image

\----------------------------------------------------------------------------*/
typedef struct _entity_image_ {
	SSL_Image *image;			/**< image of the entity */
	int max_frames;				/**< max frame per animation */
	int current_frame;			/**< current frame of the animation */
	long time_frame;			/**< time between frames */
	long next_frame;			/**< time to change frames */
} Entity_image;


/*!--------------------------------------------------------------------------
  @brief    Entity

  This object contains information about all the entity

\----------------------------------------------------------------------------*/
typedef struct _entity_ {
	Entity_image image;			/**< image information of the entity */
	Entity_pos pos;				/**< position of the entity */
	SSL_Light *light;			/**< the ligth for the entity */
} Entity;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/


Entity *create_player();

/*!--------------------------------------------------------------------------
  @brief	Destroys a entity
  @param    entity		 entity to destroy
  @return 	Void

  Destroys a entity

\-----------------------------------------------------------------------------*/
void entity_destroy(Entity *entity);

#endif
