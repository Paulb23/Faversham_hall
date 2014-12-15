#ifndef MAP_MANAGER_H_
#define MAP_MANAGER_H_

#include "SDL2/SDL.h"
#include "../../SSL/SSL.h"

SSL_Tiled_Map *load_map(char *map_name);
void load_ini(SSL_IniFile *ini, char *map_name);

#endif
