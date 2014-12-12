#include "game.h"
#include "../config.h"
#include "../window_manager.h"
#include "SDL2/SDL.h"

static void game_ticks() {
// all logic code
}

static void handle_events(SDL_Event event) {
 // all event code
}

static void game_render() {
 // all rendering code
}

void play_game() {

	int running = 1;
	SDL_Event event;

	long lastTime = SDL_GetTicks();
	const double ns = 1000.0 / MAX_TICKS_PER_SECOND;
	Uint32 timer = SDL_GetTicks();
	float delta = 0;
	double fps = 0;
	double tick = 0;
	int uptime = 0;

	while (running) {
		Uint32 now = SDL_GetTicks();
		delta += (now - lastTime) / ns;
		lastTime = now;
		SDL_RenderPresent(game_window->renderer);
		SDL_RenderClear(game_window->renderer);

		while (delta >= 1) {

			game_ticks();

			while(SDL_PollEvent(&event)) {

				handle_events(event);

				if (event.type == SDL_QUIT) {
					running = 0;
					break;
				}
			}
			tick++;
			delta--;
		}
		fps++;

		game_render();

		if (SDL_GetTicks() - timer > 1000) {
			timer += 1000;
			uptime++;
			fps = 0;
			tick = 0;
		}
	}
}
