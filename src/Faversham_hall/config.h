/*-------------------------------------------------------------------------*/
/**
   @file    config.h
   @author  P. Batty
   @brief   Implements a the configuration system for the game

   This module implements the configuration system for the game. Loads the ini
   located at the path specified.
*/
/*--------------------------------------------------------------------------*/

#ifndef CONFIG_H_
#define CONFIG_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

char *CONFIG_PATH;			/**<* path to the config file */

char *WINDOW_TITLE;			/**< the window title */

int WINDOW_WIDTH;			/**< the window width */
int WINDOW_HEIGHT;			/**< the window height */

int WINDOW_RES_WIDTH;		/**< the window resolution  width */
int WINDOW_RES_HEIGHT;		/**< the window resolution  height */

int MAX_TICKS_PER_SECOND;	/**< number of logic updates per second */

int TEXTURE_SCALING;		/**< texture scaling mode 	0 = nearest	1 = linear    2 = anisotropic	*/
int VSYNC;					/**< vsync state 	0 = off    1 = on */
int WINDOWED;				/**< windowed mode 	0 = full screen    1 = windowed */
int BORDERLESS;				/**< borderless mode 	0 = border    1 = no borders */


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Loads the config file for the program.
  @param    path		 path to the file.
  @return 	0 on success -1 on error

  Loads the config file for the program. and fill in the variables located in
  this header file. returns 0 on success -1 on error


\-----------------------------------------------------------------------------*/
int load_config(char *path);

#endif
