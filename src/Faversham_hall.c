#include "Faversham_hall/config.h"
#include "Faversham_hall/window_manager.h"
#include "Faversham_hall/game/game.h"

int main(int argc, char *argv[]) {

	load_config("../conf/config.ini");
	create_window();
	play_game();

	return 0;
}


