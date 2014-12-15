#include "map_manager.h"
#include "SDL2/SDL.h"
#include "../../SSL/SSL.h"
#include "../window_manager.h"

static char *map_path = "../extras/resources/maps/";
static char *ini_path = "../extras/resources/maps/loading/";

SSL_Tiled_Map *load_map(char *map_name) {
	char map_full_path[strlen(map_path) + strlen(map_name) + 4];
	sprintf(map_full_path, "%s%s%s", map_path, map_name, ".tmx");
	return SSL_Tiled_Map_Load(map_full_path, game_window);
}

void load_ini(SSL_IniFile *ini, char *map_name) {
	char ini_full_path[strlen(ini_path) + strlen(map_name) + 4];
	sprintf(ini_full_path, "%s%s%s", ini_path, map_name, ".ini");
	ini = SSL_IniFIle_Create();
	SSL_IniFile_Load(ini, ini_full_path);
}
