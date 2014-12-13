/*-------------------------------------------------------------------------*/
/**
   @file    asset_manager.c
   @author  P. Batty
   @brief   Implements a the asset manager.

   This module implements the asset manager.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "asset_manager.h"
#include "../SSL/SSL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/


static SSL_Hashmap *image_hashmap;
static SSL_Hashmap *sound_hashmap;
static SSL_Hashmap *font_hashmap;


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Creates the asset manager
  @return 	0 on success -1 on error

  Creates the asset manager for use.


\-----------------------------------------------------------------------------*/
int asset_manager_create() {
	if ((image_hashmap = SSL_Hashmap_Create()) == 0) {
		return -1;
	}
	if ((sound_hashmap = SSL_Hashmap_Create()) == 0) {
		return -1;
	}
	if ((font_hashmap = SSL_Hashmap_Create()) == 0) {
		return -1;
	}

	return 0;
}
