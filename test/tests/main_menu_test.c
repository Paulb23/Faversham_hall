#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/menu/main_menu.h"
#include "../../src/Faversham_hall/window_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting Main menu  Test ...\n");

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event event;

	main_menu_init();
	main_menu_event_handeler(event);
	main_menu_ticks();

	printf(" Main menu Tests passed...\n");
	return 0;
}
