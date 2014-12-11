/*-------------------------------------------------------------------------*/
/**
   @file    window_manager.h
   @author  P. Batty
   @brief   Implements a the window manager for the game

   This module implements the window manager for the game, this is where
   the window will be created, destroyed and modified.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "window_manager.h"
#include "config.h"
#include "SDL2/SDL.h"
#include "../SSL/SSL.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/


/*----------------------------------
      Sets the window flags
 ----------------------------------*/
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

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Creates the window for the game, and sets flags
  @return 	void

  Creates the window for the game and sets the flags according to the
  results of reading the config

\-----------------------------------------------------------------------------*/
void create_window() {
	game_window = SSL_Window_Create(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, 0);
	set_flags();
}


/*!--------------------------------------------------------------------------
  @brief	Destroys the window
  @return 	void

  Destroys the window.

\-----------------------------------------------------------------------------*/
void destory_window() {
	SSL_Window_Destroy(game_window);
}
