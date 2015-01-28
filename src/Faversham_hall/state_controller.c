/*-------------------------------------------------------------------------*/
/**
   @file    state_controler.c
   @author  P. Batty
   @brief   Implements a the game state controller

   This module implements the game state controller and will control
   the state of the game.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "state_controller.h"
#include "game/game.h"
#include "menu/main_menu.h"
#include "config.h"
#include "window_manager.h"
#include "SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

/*----------------------------------
      Declare globals
 ----------------------------------*/

Game_States game_state;



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

	/* loop until we get a exit signal */
	while (running) {
		Uint32 now = SDL_GetTicks();
		delta += (now - lastTime) / ns;
		lastTime = now;
		SDL_RenderPresent(game_window->renderer);
		SDL_RenderClear(game_window->renderer);

		while (delta >= 1) {

			/**
			 * Perform tick update
			 */
			switch (game_state) {
				case MAIN_MENU: {
					main_menu_ticks();
					break;
				}
				case GAME_STATE: {
					game_ticks(delta, uptime);
					break;
				}
				case EXIT: {
					running = 0;
					break;
				}
			}

			while(SDL_PollEvent(&event)) {

				/**
				 * Perform event update
				 */
				switch (game_state) {
					case MAIN_MENU: {
					    main_menu_event_handeler(event);
						break;
					}
					case GAME_STATE: {
						game_event_handle(event, uptime);
						break;
					}
					case EXIT: {
						running = 0;
						break;
					}
				}

				if (event.type == SDL_QUIT) {
					switch_state(EXIT);
				}

				if(event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT) ){
					switch_state(EXIT);
				}
			}
			tick++;
			delta--;
		}
		fps++;

		/**
		 * Perform render update
		 */
		switch (game_state) {
			case MAIN_MENU: {
				main_menu_renderer();
				break;
			}
			case GAME_STATE: {
				game_render();
				break;
			}
			case EXIT: {
				running = 0;
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


/*!--------------------------------------------------------------------------
  @brief	Switches the game state
  @param	new_state		The state to switch to
  @return 	Void

  Switches the game state

\-----------------------------------------------------------------------------*/
void switch_state(Game_States new_state) {


	if (game_state) {
		/* clean up the previous state */
		switch (game_state) {
			case MAIN_MENU: {
				main_menu_clean_up();
				break;
			}
			case GAME_STATE: {
				game_clean_up(new_state);
				break;
			}
			case EXIT: {
				break;
			}
		}
	}

	/* init the new state */
	switch (new_state) {
		case MAIN_MENU: {
			main_menu_init();
			break;
		}
		case GAME_STATE: {
			game_init(0);
			break;
		}
		case GAME_LOAD_STATE: {
			new_state = GAME_STATE;
			game_init(1);
			break;
		}
		case EXIT: {
			break;
		}
	}

	/* switch to the new state */
	game_state = new_state;
}
