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
#include "../objects/ai.h"
#include "../objects/entity.h"
#include "mission_manager.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static char *map_path = "../extras/resources/maps/";			/**< Path to the .tmx */
static char *ini_path = "../extras/resources/maps/loading/";	/**< Path to the .ini */


/*------------------------------------------------------------
    Checks tiles around a point to see if they are empty
 -----------------------------------------------------------*/

static int check_around_for_empty(SSL_Tiled_Map *map, int x, int y, int layer_index) {
	if (SSL_Tiled_Get_TileId(map, x, y, layer_index) != 0) {return 0;}
	if (SSL_Tiled_Get_TileId(map, x + 1, y, layer_index) != 0) {return 0;}
	if (SSL_Tiled_Get_TileId(map, x - 1, y, layer_index) != 0) {return 0;}
	if (SSL_Tiled_Get_TileId(map, x, y + 1, layer_index) != 0) {return 0;}
	if (SSL_Tiled_Get_TileId(map, x, y - 1, layer_index) != 0) {return 0;}
	if (SSL_Tiled_Get_TileId(map, x + 1, y + 1, layer_index) != 0) {return 0;}
	if (SSL_Tiled_Get_TileId(map, x + 1, y - 1, layer_index) != 0) {return 0;}
	if (SSL_Tiled_Get_TileId(map, x - 1, y + 1, layer_index) != 0) {return 0;}
	if (SSL_Tiled_Get_TileId(map, x - 1, y - 1, layer_index) != 0) {return 0;}

	return 1;
}

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
	char map_full_path[strlen(map_path) + strlen(map_name) + 4];	// join the path with the name
	sprintf(map_full_path, "%s%s%s", map_path, map_name, ".tmx");
	return SSL_Tiled_Map_Load(map_full_path, game_window);			// load and return the name
}


/*!--------------------------------------------------------------------------
  @brief	Loads a ini
  @param	map_name		The ini name
  @return 	Loaded .ini file

  Loads a ini given a name

\-----------------------------------------------------------------------------*/
SSL_IniFile *load_ini(char *map_name) {
	char ini_full_path[strlen(ini_path) + strlen(map_name) + 4];  // join the path with the name
	sprintf(ini_full_path, "%s%s%s", ini_path, map_name, ".ini");
	SSL_IniFile *ini = SSL_IniFIle_Create();
	SSL_IniFile_Load(ini, ini_full_path);						  // load and return
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
	int layer = SSL_Tiled_Get_LayerIndex(map, "other");			// get the light layer

	for (i = 0; i < SSL_Tiled_Get_Width(map); i++) {			// loop through the map
		for (j = 0; j < SSL_Tiled_Get_Height(map); j++) {
			if(SSL_Tiled_Get_TileId(map, i, j, layer) == 2) {	// if we hit a light create and add it
				SSL_Light *light = SSL_Light_Create(i *16, j *16, 0, 0, 4, 0, SSL_Color_Create(255,255,255,255));
				SSL_Tiled_Add_Light(map, light);
			}
		}
	}
}


/*!--------------------------------------------------------------------------
  @brief	Load ai
  @param	map		Map to load the ai on
  @param	list	The list to add the ai to
  @return 	Void

  Loads and add the ai to the map and list.

\-----------------------------------------------------------------------------*/
void load_ai(SSL_Tiled_Map *map, SSL_List *list) {
	int i;
	int j;
	int layer = SSL_Tiled_Get_LayerIndex(map, "characters");	// get the ai layer

	for (i = 0; i < SSL_Tiled_Get_Width(map); i++) {			// loop through the map
		for (j = 0; j < SSL_Tiled_Get_Height(map); j++) {
			int tile_id = SSL_Tiled_Get_TileId(map, i, j, layer);
			if (tile_id != 0) {									// if we hit a ai, create the correct one, based on tile id
				AI *ai;

				switch(tile_id) {
					case 1: {
						ai = ai_create("butler");
					}
					break;
					case 2: {
						ai = ai_create("chef");
					}
					break;
					case 3: {
						ai = ai_create("maid");
					}
					break;
					case 4: {
						ai = ai_create("dutchess");
					}
					break;
					case 5: {
						ai = ai_create("nephew");
					}
					break;
					case 6: {
						ai = ai_create("soninlaw");
					}
					break;
					case 7: {
						ai = ai_create("twins");
					}
					break;
					case 8: {
						ai = ai_create("nanny");
					}
					break;
					case 9: {
						ai = ai_create("servant");
					}
					break;
					case 10: {
						ai = ai_create("companion");
					}
					break;
				}
				if (tile_id == 9 && get_current_act() != 6 && get_current_act() != 8) {

				} else {
																	// set up the ai's light and position
					entity_set_pos((Entity *)&ai->entity, i * SSL_Tiled_Get_Tile_Width(map), j * SSL_Tiled_Get_Tile_Height(map));
					SSL_Light_SetPos(ai->entity.light, ai->entity.pos.x ,ai->entity.pos.y);
					if (get_current_act() == 6 && get_current_mission() == 0) {
						ai->entity.light->range = 2;
					}
					SSL_Tiled_Add_Light(map, ai->entity.light);
					SSL_List_Add(list, ai);
				}
			}
		}
	}
}


/*!--------------------------------------------------------------------------
  @brief	Could place the servant
  @param	map		Map to load the servant on
  @param	list	The list to add the servant to
  @return 	Void

  Loads and add the servant to the map and list.

\-----------------------------------------------------------------------------*/
void load_servant(SSL_Tiled_Map *map, SSL_List *list) {
	int num = rand() % 100 + 0;
	if (num < 20) {	/* 20% chance */
		AI *ai = ai_create("servant");
		int valid = 0;
		int i = 0;
		int j = 0;

		int other = SSL_Tiled_Get_LayerIndex(map, "other");				// get the layer to check
		int puzzle = SSL_Tiled_Get_LayerIndex(map, "puzzle");
		int characters = SSL_Tiled_Get_LayerIndex(map, "characters");
		int lighting = SSL_Tiled_Get_LayerIndex(map, "lighting");
		int collsion = SSL_Tiled_Get_LayerIndex(map, "collsion");

		while (valid == 0) {											// loop until we hit a valid spot
			i = rand() % SSL_Tiled_Get_Width(map);						// genorate new x,y coords
			j = rand() % SSL_Tiled_Get_Height(map);

			if (check_around_for_empty(map, i, j, other)) {				// check for empty squares
				if (check_around_for_empty(map, i, j, puzzle)) {
					if (check_around_for_empty(map, i, j, characters)) {
						if (check_around_for_empty(map, i, j, lighting)) {
							if (check_around_for_empty(map, i, j, collsion)) {
								valid = 1;								// if so exit the loop
							}
						}
					}
				}
			}
		}

		int  id = 4;													// the talking tile id code
																		// set the "talking zone"
		SSL_Tiled_Set_TiledID(map, other, i, j, id);
		SSL_Tiled_Set_TiledID(map, other, i + 1, j, id);
		SSL_Tiled_Set_TiledID(map, other, i - 1, j, id);
		SSL_Tiled_Set_TiledID(map, other, i, j + 1, id);
		SSL_Tiled_Set_TiledID(map, other, i, j - 1, id);
		SSL_Tiled_Set_TiledID(map, other, i + 1, j + 1, id);
		SSL_Tiled_Set_TiledID(map, other, i + 1, j - 1, id);
		SSL_Tiled_Set_TiledID(map, other, i - 1, j + 1, id);
		SSL_Tiled_Set_TiledID(map, other, i - 1, j - 1, id);

																		// set up the ai's light and position
		entity_set_pos((Entity *)&ai->entity, i * SSL_Tiled_Get_Tile_Width(map), j * SSL_Tiled_Get_Tile_Height(map));
		SSL_Light_SetPos(ai->entity.light, ai->entity.pos.x ,ai->entity.pos.y);
		SSL_Tiled_Add_Light(map, ai->entity.light);
		SSL_List_Add(list, ai);
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
