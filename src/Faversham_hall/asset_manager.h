/*-------------------------------------------------------------------------*/
/**
   @file    asset_manager.h
   @author  P. Batty
   @brief   Implements a the asset manager.

   This module implements the asset manager.
*/
/*--------------------------------------------------------------------------*/

#ifndef ASSET_MANAGER_H_
#define ASSET_MANAGER_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/


#include "SDL2/SDL.h"
#include "../SSL/SSL.h"

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Asset_types

  Different asset type, will determine how they will be stored and retrieved.
	  ASSET_IMAGE - SSL_Image
	  ASSET_SOUND - Mix_Chunk
	  ASSET_FONT  - SSL_Font
	  ASSET_MAP   - SSL_Tiled_Map

\----------------------------------------------------------------------------*/
typedef enum {
	ASSET_IMAGE,
	ASSET_SOUND,
	ASSET_FONT,
} Asset_Types;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Creates the asset manager
  @return 	0 on success -1 on error

  Creates the asset manager for use.


\-----------------------------------------------------------------------------*/
int asset_manager_create();


#endif
