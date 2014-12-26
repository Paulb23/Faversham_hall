/*-------------------------------------------------------------------------*/
/**
   @file    map_manager.h
   @author  P. Batty
   @brief   Manages the map for the game

   This module implements the map manager, loads, and handles all map
   functions.
*/
/*--------------------------------------------------------------------------*/

#ifndef MAP_MANAGER_H_
#define MAP_MANAGER_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"
#include "../../SSL/SSL.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Loads a map
  @param	map_name		The map name
  @return 	Loaded .tmx map

  Loads a map given a name

\-----------------------------------------------------------------------------*/
SSL_Tiled_Map *load_map(char *map_name);


/*!--------------------------------------------------------------------------
  @brief	Loads a ini
  @param	map_name		The ini name
  @return 	Loaded .ini file

  Loads a ini given a name

\-----------------------------------------------------------------------------*/
SSL_IniFile *load_ini(char *map_name);


/*!--------------------------------------------------------------------------
  @brief	Load lights
  @param	map		Map to load the lights on
  @return 	Void

  Loads and add the lights to the map

\-----------------------------------------------------------------------------*/
void load_lights(SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief	Load ai
  @param	map		Map to load the ai on
  @param	list	The list to add the ai to
  @return 	Void

  Loads and add the ai to the map and list.

\-----------------------------------------------------------------------------*/
void load_ai(SSL_Tiled_Map *map, SSL_List *list);


/*!--------------------------------------------------------------------------
  @brief	Could place the servant
  @param	map		Map to load the servant on
  @param	list	The list to add the servant to
  @return 	Void

  Loads and add the servant to the map and list.

\-----------------------------------------------------------------------------*/
void load_servant(SSL_Tiled_Map *map, SSL_List *list);


/*!--------------------------------------------------------------------------
  @brief	raytrace for lights

\-----------------------------------------------------------------------------*/
int raytrace(int x, int y, void *map1);

#endif
