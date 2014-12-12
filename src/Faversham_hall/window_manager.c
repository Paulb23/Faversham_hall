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
static int set_flags() {
	char result;
	itoa(TEXTURE_SCALING, &result, 10);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, &result);

	itoa(VSYNC, &result, 10);
	SDL_SetHint( SDL_HINT_RENDER_VSYNC, &result );

	SDL_SetWindowBordered(game_window->window, !BORDERLESS);

	if (!WINDOWED) {
		if(SDL_SetWindowFullscreen(game_window->window, WINDOWED) == -1) {
			SSL_Log_Write("Error: unable to set to full screen");
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window", "Could not create fullscreen Window.", NULL);
			return -1;
		}
	}

	return 0;
}

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Creates the window for the game, and sets flags
  @return 	0 on success else -1

  Creates the window for the game and sets the flags according to the
  results of reading the config

\-----------------------------------------------------------------------------*/
int create_window() {
	game_window = SSL_Window_Create(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, 0);
	if (game_window == 0) {
		SSL_Log_Write("Error: unable to create window");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window", "Could not create Window.", NULL);
		return -1;
	}
	return set_flags();
}


/*!--------------------------------------------------------------------------
  @brief	Destroys the window
  @return 	void

  Destroys the window.

\-----------------------------------------------------------------------------*/
void destory_window() {
	SSL_Window_Destroy(game_window);
}
