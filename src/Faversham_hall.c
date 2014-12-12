#include "Faversham_hall/config.h"
#include "Faversham_hall/window_manager.h"
#include "Faversham_hall/game/game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_Mixer.h"
#include "SDL2/SDL_Image.h"
#include "SDL2/SDL_TTF.h"
#include "SSL/SSL.h"

int main(int argc, char *argv[]) {

	// init libaries
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
	SSL_Init();

	load_config("../conf/config.ini");
	create_window();
	play_game();

	return 0;
}


