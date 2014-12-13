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
#include "SDL2/SDL_Mixer.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/


static SSL_Hashmap *image_hashmap;		/**< Hashmap for the images    */
static SSL_Hashmap *sound_hashmap;		/**< Hashmap for the sounds	   */
static SSL_Hashmap *font_hashmap;		/**< Hashmap for the fonts 	   */
static SSL_Hashmap *other_hashmap;		/**< Hashmap for other objects */


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
	if ((other_hashmap = SSL_Hashmap_Create()) == 0) {
		return -1;
	}

	return 0;
}


/*!--------------------------------------------------------------------------
  @brief	Adds a image to the asset manager
  @param	name		Name of the object must be unique
  @param 	object		The image to add
  @return 	void

  Adds a image to the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_addImage(char *name, SSL_Image *object) {
	SSL_Hashmap_Add(image_hashmap, name, object);
}


/*!--------------------------------------------------------------------------
  @brief	Adds a sound to the asset manager
  @param	name		Name of the object must be unique
  @param 	object		The sound to add
  @return 	void

  Adds a sound to the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_addSound(char *name, Mix_Chunk *object) {
	SSL_Hashmap_Add(sound_hashmap, name, object);
}


/*!--------------------------------------------------------------------------
  @brief	Adds a font to the asset manager
  @param	name		Name of the object must be unique
  @param 	object		The font to add
  @return 	void

  Adds a font to the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_addFont(char *name, SSL_Font *object) {
	SSL_Hashmap_Add(font_hashmap, name, object);
}


/*!--------------------------------------------------------------------------
  @brief	Adds anything to the asset manager
  @param	name		Name of the object must be unique
  @param 	object		anything to add
  @return 	void

  Adds anything to the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_addOther(char *name, void *object) {
	SSL_Hashmap_Add(other_hashmap, name, object);
}


/*!--------------------------------------------------------------------------
  @brief	Gets a image from the asset manager
  @param	name		Name of the object to get
  @return 	The Image object

  Gets a image from the asset manager

\-----------------------------------------------------------------------------*/
SSL_Image *asset_manager_getImage(char *name) {
	return (SSL_Image *)SSL_Hashmap_Get(image_hashmap, name);
}


/*!--------------------------------------------------------------------------
  @brief	Gets a sound from the asset manager
  @param	name		Name of the object to get
  @return 	The Sound object

  Gets a sound from the asset manager

\-----------------------------------------------------------------------------*/
Mix_Chunk *asset_manager_getSound(char *name) {
	return (Mix_Chunk *)SSL_Hashmap_Get(sound_hashmap, name);
}


/*!--------------------------------------------------------------------------
  @brief	Gets a font from the asset manager
  @param	name		Name of the object to get
  @return 	The Image object

  Gets a font from the asset manager

\-----------------------------------------------------------------------------*/
SSL_Font *asset_manager_getFont(char *name) {
	return (SSL_Font *)SSL_Hashmap_Get(font_hashmap, name);
}


/*!--------------------------------------------------------------------------
  @brief	Gets anything from the asset manager
  @param	name		Name of the object to get
  @return 	The anything object

  Gets a anything from the asset manager

\-----------------------------------------------------------------------------*/
void *asset_manager_getOther(char *name) {
	return (void *)SSL_Hashmap_Get(other_hashmap, name);
}


/*!--------------------------------------------------------------------------
  @brief	Removes a image from the asset manager
  @param	name		Name of the object to remove
  @return 	Void

  Removes a image from the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_removeImage(char *name) {
	SSL_Hashmap_Remove(image_hashmap, name);
}


/*!--------------------------------------------------------------------------
  @brief	Removes a sound from the asset manager
  @param	name		Name of the object to remove
  @return 	Void

  Removes a sound from the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_removeSound(char *name) {
	SSL_Hashmap_Remove(sound_hashmap, name);
}


/*!--------------------------------------------------------------------------
  @brief	Removes a font from the asset manager
  @param	name		Name of the object to remove
  @return 	Void

  Removes a font from the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_removeFont(char *name) {
	SSL_Hashmap_Remove(font_hashmap, name);
}


/*!--------------------------------------------------------------------------
  @brief	Removes anything from the asset manager
  @param	name		Name of the object to remove
  @return 	Void

  Removes a anything from the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_removeOther(char *name) {
	SSL_Hashmap_Remove(other_hashmap, name);
}
