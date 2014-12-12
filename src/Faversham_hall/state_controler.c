/*-------------------------------------------------------------------------*/
/**
   @file    state_controler.h
   @author  P. Batty
   @brief   Implements a the game state controller

   This module implements the game state controller and will control
   the state of the game.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "state_controler.h"
#include "game/game.h"
#include "config.h"
#include "window_manager.h"
#include "SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Starts the game
  @return 	Void

  Starts the game.

\-----------------------------------------------------------------------------*/
void start_game() {

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

		switch (game_state) {
			case MAIN_MENU: {
				// main_menu_ticks();
				break;
			}
			case GAME_STATE: {
				game_ticks(delta, uptime);
				break;
			}
		}

			while(SDL_PollEvent(&event)) {

				switch (game_state) {
					case MAIN_MENU: {
						// main_menu_event_handeler();
						break;
					}
					case GAME_STATE: {
						game_event_handle(event, uptime);
						break;
					}
				}

				if (event.type == SDL_QUIT) {
					running = 0;
					break;
				}
			}
			tick++;
			delta--;
		}
		fps++;

		switch (game_state) {
			case MAIN_MENU: {
				// main_menu_renderer();
				break;
			}
			case GAME_STATE: {
				game_render();
				break;
			}
		}

		if (SDL_GetTicks() - timer > 1000) {
			timer += 1000;
			uptime++;
			fps = 0;
			tick = 0;
		}
	}
}
