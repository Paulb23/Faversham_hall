#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/game/map_manager.h"
#include "../../src/Faversham_hall/window_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting Map Manager  Test ...\n");

	create_window();
	SSL_Tiled_Map *map = SSL_Tiled_Map_Load("../../extras/resources/maps/test_map.tmx", game_window);
	load_lights(map);
	load_ai(map, SSL_List_Create());
	load_servant(map, SSL_List_Create());
	raytrace(0,0,map);

	printf(" Map Manager Tests passed...\n");
	return 0;
}
