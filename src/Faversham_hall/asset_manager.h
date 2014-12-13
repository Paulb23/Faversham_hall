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
#include "SDL2/SDL_Mixer.h"
#include "../SSL/SSL.h"

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Creates the asset manager
  @return 	0 on success -1 on error

  Creates the asset manager for use.


\-----------------------------------------------------------------------------*/
int asset_manager_create();


/*!--------------------------------------------------------------------------
  @brief	Adds a image to the asset manager
  @param	name		Name of the object must be unique
  @param 	object		The image to add
  @return 	void

  Adds a image to the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_addImage(char *name, SSL_Image *object);


/*!--------------------------------------------------------------------------
  @brief	Adds a sound to the asset manager
  @param	name		Name of the object must be unique
  @param 	object		The sound to add
  @return 	void

  Adds a sound to the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_addSound(char *name, Mix_Chunk *object);


/*!--------------------------------------------------------------------------
  @brief	Adds a font to the asset manager
  @param	name		Name of the object must be unique
  @param 	object		The font to add
  @return 	void

  Adds a font to the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_addFont(char *name, SSL_Font *object);


/*!--------------------------------------------------------------------------
  @brief	Adds anything to the asset manager
  @param	name		Name of the object must be unique
  @param 	object		anything to add
  @return 	void

  Adds anything to the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_addOther(char *name, void *object);


/*!--------------------------------------------------------------------------
  @brief	Gets a image from the asset manager
  @param	name		Name of the object to get
  @return 	The Image object

  Gets a image from the asset manager

\-----------------------------------------------------------------------------*/
SSL_Image *asset_manager_getImage(char *name);


/*!--------------------------------------------------------------------------
  @brief	Gets a sound from the asset manager
  @param	name		Name of the object to get
  @return 	The Sound object

  Gets a sound from the asset manager

\-----------------------------------------------------------------------------*/
Mix_Chunk *asset_manager_getSound(char *name);


/*!--------------------------------------------------------------------------
  @brief	Gets a font from the asset manager
  @param	name		Name of the object to get
  @return 	The Image object

  Gets a font from the asset manager

\-----------------------------------------------------------------------------*/
SSL_Font *asset_manager_getFont(char *name);


/*!--------------------------------------------------------------------------
  @brief	Gets anything from the asset manager
  @param	name		Name of the object to get
  @return 	The anything object

  Gets a anything from the asset manager

\-----------------------------------------------------------------------------*/
void *asset_manager_getOther(char *name);


/*!--------------------------------------------------------------------------
  @brief	Removes a image from the asset manager
  @param	name		Name of the object to remove
  @return 	Void

  Removes a image from the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_removeImage(char *name);


/*!--------------------------------------------------------------------------
  @brief	Removes a sound from the asset manager
  @param	name		Name of the object to remove
  @return 	Void

  Removes a sound from the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_removeSound(char *name);


/*!--------------------------------------------------------------------------
  @brief	Removes a font from the asset manager
  @param	name		Name of the object to remove
  @return 	Void

  Removes a font from the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_removeFont(char *name);


/*!--------------------------------------------------------------------------
  @brief	Removes anything from the asset manager
  @param	name		Name of the object to remove
  @return 	Void

  Removes a anything from the asset manager

\-----------------------------------------------------------------------------*/
void asset_manager_removeOther(char *name);


/*!--------------------------------------------------------------------------
  @brief	Removes everything from the asset manager, and start it up again
  @return 	0 on success -1 on error

  Removes everything from the asset manager, and start it up again

\-----------------------------------------------------------------------------*/
int asset_manager_reset() ;


#endif
