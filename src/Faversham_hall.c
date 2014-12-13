#include "Faversham_hall/state_controller.h"
#include "Faversham_hall/config.h"
#include "Faversham_hall/window_manager.h"
#include "Faversham_hall/asset_manager.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_Mixer.h"
#include "SDL2/SDL_Image.h"
#include "SDL2/SDL_TTF.h"
#include "SSL/SSL.h"

int main(int argc, char *argv[]) {

	// init libaries
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SSL_Log_Write("FATAL: Could not start SDL 2!");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL 2", "FATAL: Could not start SDL 2!", NULL);
		return 1;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SSL_Log_Write("FATAL: Could not start SDL Image!");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Image", "FATAL: Could not start SDL Image!", NULL);
		return 1;
	}
	if(Mix_Init(MIX_INIT_MP3) == 0) {
		SSL_Log_Write("FATAL: Could not start SDL Mixer!");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer", "FATAL: Could not start SDL Mixer!", NULL);
		return 1;
	}
	Mix_OpenAudio(22050, AUDIO_S16SYS, 10, 4096);

	if(SSL_Init() == 0) {
		SSL_Log_Write("FATAL: Could not start SSL!");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SSL", "FATAL: Could not start SSL!", NULL);
		return 1;
	}

	// load stuff and start the game
	if(load_config("../conf/config.ini") != 0) {
		return 1;
	}
	if (asset_manager_create() != 0) {
		SSL_Log_Write("FATAL: Could not create Asset manager!");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Asset Manager", "FATAL: Could not create Asset manager!", NULL);
		return -1;
	}
	if(create_window()) {
		return 1;
	}

	switch_state(GAME_STATE);
	start_game();

	return 0;
}


