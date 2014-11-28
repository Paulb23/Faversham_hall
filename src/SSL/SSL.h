/*-------------------------------------------------------------------------*/
/**
   @file    SSL.h
   @author  P. Batty
   @brief   Includes all the SSL modules and init function

   This module includes all the SSL modules and init function

*/
/*--------------------------------------------------------------------------*/

#ifndef SDL_GAME_API_H_
#define SDL_GAME_API_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Settings.h"

#include "files/iniparser.h"
#include "files/SSL_Tiled.h"

#include "misc/SSL_Logger.h"
#include "misc/SSL_Keys.h"
#include "misc/SSL_Hashmap.h"
#include "misc/SSL_Color.h"
#include "misc/SSL_Rectangle.h"
#include "misc/SSL_List.h"
#include "misc/SSL_String.h"

#include "graphics/SSL_Window.h"
#include "graphics/SSL_Image.h"
#include "graphics/SSL_Font.h"

#include "input/SSL_Keyboard.h"
#include "input/SSL_Mouse.h"

#include "gui/SSL_Interface.h"
#include "gui/SSL_Button.h"

#include "timing/SSL_Timing.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    initialises the library
  @return 1 on success else 0

  initialises the library

\-----------------------------------------------------------------------------*/
int SSL_Init();


#endif
