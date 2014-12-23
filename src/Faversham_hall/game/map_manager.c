/*-------------------------------------------------------------------------*/
/**
   @file    map_manager.c
   @author  P. Batty
   @brief   Manages the map for the game

   This module implements the map manager, loads, and handles all map
   functions.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "map_manager.h"
#include "SDL2/SDL.h"
#include "../../SSL/SSL.h"
#include "../window_manager.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static char *map_path = "../extras/resources/maps/";			/**< Path to the .tmx */
static char *ini_path = "../extras/resources/maps/loading/";	/**< Path to the .ini */


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Loads a map
  @param	map_name		The map name
  @return 	Loaded .tmx map

  Loads a map given a name

\-----------------------------------------------------------------------------*/
SSL_Tiled_Map *load_map(char *map_name) {
	char map_full_path[strlen(map_path) + strlen(map_name) + 4];
	sprintf(map_full_path, "%s%s%s", map_path, map_name, ".tmx");
	return SSL_Tiled_Map_Load(map_full_path, game_window);
}


/*!--------------------------------------------------------------------------
  @brief	Loads a ini
  @param	map_name		The ini name
  @return 	Loaded .ini file

  Loads a ini given a name

\-----------------------------------------------------------------------------*/
SSL_IniFile *load_ini(char *map_name) {
	char ini_full_path[strlen(ini_path) + strlen(map_name) + 4];
	sprintf(ini_full_path, "%s%s%s", ini_path, map_name, ".ini");
	SSL_IniFile *ini = SSL_IniFIle_Create();
	SSL_IniFile_Load(ini, ini_full_path);
	return ini;
}


/*!--------------------------------------------------------------------------
  @brief	Load lights
  @param	map		Map to load the lights on
  @return 	Void

  Loads and add the lights to the map

\-----------------------------------------------------------------------------*/
void load_lights(SSL_Tiled_Map *map) {
	int i;
	int j;
	int layer = SSL_Tiled_Get_LayerIndex(map, "other");

	for (i = 0; i < SSL_Tiled_Get_Width(map); i++) {
		for (j = 0; j < SSL_Tiled_Get_Height(map); j++) {
			if(SSL_Tiled_Get_TileId(map, i, j, layer) == 2) {
				SSL_Light *light = SSL_Light_Create(i *16, j *16, 0, 0, 4, 0, SSL_Color_Create(255,255,255,255));
				SSL_Tiled_Add_Light(map, light);
			}
		}
	}
}


/*!--------------------------------------------------------------------------
  @brief	raytrace for lights

\-----------------------------------------------------------------------------*/
int raytrace(int x, int y, void *map1) {
	   SSL_Tiled_Map *map = (SSL_Tiled_Map *)map1;
	   int layer = SSL_Tiled_Get_LayerIndex(map, "lighting");
       if(SSL_Tiled_Get_TileId(map,x/map->map.tile_width,y/map->map.tile_height, layer) == 1) {
    	    return 1;
        }
    return 0;
}
