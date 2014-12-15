#include "map_manager.h"
#include "SDL2/SDL.h"
#include "../../SSL/SSL.h"
#include "../window_manager.h"

static char *map_path = "../extras/resources/maps/";
static char *ini_path = "../extras/resources/maps/loading/";

static int SSL_Tiled_Get_Tile_FrameNumber(SSL_Tiled_Map *map, int tile_id) {
	 SSL_Tileset *tileset;
	 int k;
	 if (map->map.total_tilesets != 1) {
		 for (k = 0; k < SSL_List_Size(map->tilesets)-1; k++) {
			 tileset = SSL_List_Get(map->tilesets, k+1);
			 if (tile_id < tileset->firstGid || tileset == NULL) {
				 tileset = SSL_List_Get(map->tilesets, k);
				 break;
			 }
		 }
	 } else {
		 k = 0;
		 tileset = SSL_List_Get(map->tilesets, k);
	 }
	 int frame = 1;

	 if (k != 0) {
		 frame = tile_id - (tileset->firstGid - 1);
	 } else {
		 frame = tile_id;
	 }

 return frame;
}

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

void load_lights(SSL_Tiled_Map *map) {
	int i;
	int j;

	for (i = 0; i < SSL_Tiled_Get_Width(map); i++) {
		for (j = 0; j < SSL_Tiled_Get_Width(map); j++) {
			if (SSL_Tiled_Get_Tile_FrameNumber(map, SSL_Tiled_Get_TileId(map, i ,j, SSL_Tiled_Get_LayerIndex(map, "other"))) == 1) {
				SSL_Tiled_Add_Light(map, SSL_Light_Create(i * SSL_Tiled_Get_Tile_Width(map), j * SSL_Tiled_Get_Tile_Height(map), 0, 0, 7, 0, SSL_Color_Create(0,0,0,255)));
			}
		}
	}
}
