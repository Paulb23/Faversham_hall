#ifndef MAP_MANAGER_H_
#define MAP_MANAGER_H_

#include "SDL2/SDL.h"
#include "../../SSL/SSL.h"

void load_map(SSL_Tiled_Map *map, char *map_name);
void load_ini(SSL_IniFile *ini, char *map_name);
void load_lights(SSL_Tiled_Map *map);

#endif
