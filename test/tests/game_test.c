#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/game/game.h"
#include "../../src/Faversham_hall/window_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting Game  Test ...\n");

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event event;

	game_get_dialog_node_name();
	game_get_room();
	game_get_talking_ai();
	game_in_dialog();


	printf(" Game Tests passed...\n");
	return 0;
}
