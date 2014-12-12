/*-------------------------------------------------------------------------*/
/**
   @file    game.h
   @author  P. Batty
   @brief   Implements a the game loop

   This module implements the game loop
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "game.h"
#include "../config.h"
#include "../window_manager.h"
#include "SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/


/*----------------------------------
      Logic code
 ----------------------------------*/
static void game_ticks(double delta, int uptime) {

}


/*----------------------------------
      Event code
 ----------------------------------*/
static void handle_events(SDL_Event event, int uptime) {

}


/*----------------------------------
      Render code
 ----------------------------------*/
static void game_render() {

}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Starts the game
  @return 	Void

  Starts the game.

\-----------------------------------------------------------------------------*/
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

			game_ticks(delta, uptime);

			while(SDL_PollEvent(&event)) {

				handle_events(event, uptime);

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
