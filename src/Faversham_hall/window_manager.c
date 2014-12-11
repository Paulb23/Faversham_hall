#include "window_manager.h"
#include "config.h"
#include "SDL2/SDL.h"
#include "../SSL/SSL.h"

static void set_flags() {
	char result;
	itoa(TEXTURE_SCALING, &result, 10);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, &result);

	itoa(VSYNC, &result, 10);
	SDL_SetHint( SDL_HINT_RENDER_VSYNC, &result );

	SDL_SetWindowBordered(game_window->window, BORDERLESS);

	if (!WINDOWED) {
		SDL_SetWindowFullscreen(game_window->window, WINDOWED);
	}
}

void create_window() {
	game_window = SSL_Window_Create(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, 0);
	set_flags();
}

void destory_window() {
	SSL_Window_Destroy(game_window);
}
