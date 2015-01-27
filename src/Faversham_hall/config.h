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

extern char *CONFIG_PATH;			/**<* path to the config file */

extern char *WINDOW_TITLE;			/**< the window title */

extern int WINDOW_WIDTH;			/**< the window width */
extern int WINDOW_HEIGHT;			/**< the window height */

extern int WINDOW_RES_WIDTH;		/**< the window resolution  width */
extern int WINDOW_RES_HEIGHT;		/**< the window resolution  height */

extern int MAX_TICKS_PER_SECOND;	/**< number of logic updates per second */

extern int TEXTURE_SCALING;			/**< texture scaling mode 	0 = nearest	1 = linear    2 = anisotropic	*/
extern int VSYNC;					/**< vsync state 	0 = off    1 = on */
extern int WINDOWED;				/**< windowed mode 	0 = full screen    1 = windowed */
extern int BORDERLESS;				/**< borderless mode 	0 = border    1 = no borders */

extern char *UP_KEY;				/**< the up moment key */
extern char *DOWN_KEY;				/**< the down moment key */
extern char *LEFT_KEY;				/**< the left moment key */
extern char *RIGHT_KEY;				/**< the right moment key */
extern char *INTERACT_KEY;			/**< the interact moment key */
extern char *PAUSE_KEY;				/**< the interact moment key */


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
