#include "window_manager.h"
#include "config.h"
#include "SDL2/SDL.h"
#include "../SSL/SSL.h"

void create_window() {
	game_window = SSL_Window_Create(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, 0);
}

void destory_window() {
	SSL_Window_Destroy(game_window);
}
