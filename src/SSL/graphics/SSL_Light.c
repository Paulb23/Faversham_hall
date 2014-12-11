/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Light.c
   @author  P. Batty
   @brief   Implements a Light object, used in tiled maps for tile based lighting

   This module implements a light object that can be added to any SSL_Tiled_Map
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Light.h"
#include "../misc/SSL_Logger.h"
#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new Light object
  @param    x			  X position of the light
  @param    y			  Y position of the light
  @param	width		  width of the light
  @param	angle		  angle of the light
  @param	range		  range of the light
  @param	fade		  Should the light fade boolean, 1 / 0
  @param	color		  Color of the light
  @param	brightness	  brightness of the light
  @return An new SSL_Light object or -1 or fail

  Creates a new SSL_Light object or -1 on error

\-----------------------------------------------------------------------------*/
SSL_Light *SSL_Light_Create(int x, int y, int width, int angle, int range, int fade, SDL_Color color, int brightness) {
	SSL_Light *light = malloc(sizeof(SSL_Light));

	if (!light) {
		free(light);
		SSL_Log_Write("Error allocation memory for light!");
		return (void *)-1;
	}

	light->x = x;
	light->y = y;
	light->width = width;
	light->angle = angle;
	light->range = range;
	light->fade = fade;
	light->color = color;
	light->brightness = brightness;

  return light;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the x position of the light
  @param    light		  light object to get the x position of.
  @return X position of the light

  Gets the x position of the light

\-----------------------------------------------------------------------------*/
int SSL_Light_GetX(SSL_Light *light) {
	return light->x;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the y position of the light
  @param    light		  light object to get the y position of.
  @return Y position of the light

  Gets the y position of the light

\-----------------------------------------------------------------------------*/
int SSL_Light_GetY(SSL_Light *light) {
	return light->y;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the angle of the light
  @param    light		  light object to get the angle of.
  @return Angle of the light

  Gets the angle position of the light

\-----------------------------------------------------------------------------*/
int SSL_Light_GetAngle(SSL_Light *light) {
	return light->angle;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the width of the light
  @param    light		  light object to get the width of.
  @return Width of the light

  Gets the width of the light

\-----------------------------------------------------------------------------*/
int SSL_Light_GetWidth(SSL_Light *light) {
	return light->width;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the range of the light
  @param    light		  light object to get the range of.
  @return Range of the light

  Gets the range of the light

\-----------------------------------------------------------------------------*/
int SSL_Light_GetRange(SSL_Light *light) {
	return light->range;
}


/*!--------------------------------------------------------------------------
  @brief    Gets whether the light fades
  @param    light		  light object to get the whether it fades
  @return 1 if it fades else 0

  Gets whether the light fades

\-----------------------------------------------------------------------------*/
int SSL_Light_GetFade(SSL_Light *light) {
	return light->fade;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the brightness of the light
  @param    light		  light object to get the brightness of.
  @return Brightness of the light

  Gets the brightness of the light

\-----------------------------------------------------------------------------*/
int SSL_Light_GetBrightness(SSL_Light *light) {
	return light->brightness;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the color of the light
  @param    light		  light object to get the color of.
  @return Color of the light

  Gets the color of the light

\-----------------------------------------------------------------------------*/
SDL_Color SSL_Light_GetColor(SSL_Light *light) {
	return light->color;
}


/*!--------------------------------------------------------------------------
  @brief    Sets the position of the light
  @param    light		  light object to set the position of
  @param    x		  	  new x position of the light
  @param    y		  	  new y position of the light
  @return Void

  Sets the position of the light

\-----------------------------------------------------------------------------*/
void SSL_Light_SetPos(SSL_Light *light, int x, int y) {
	light->x = x;
	light->y = y;
}


/*!--------------------------------------------------------------------------
  @brief    Sets the angle of the light
  @param    light		  light object to set the angle of
  @param    angle		  new angle of the light
  @return Void

  Sets the angle of the light

\-----------------------------------------------------------------------------*/
void SSL_Light_SetAngle(SSL_Light *light, int angle) {
	light->angle = angle;
}


/*!--------------------------------------------------------------------------
  @brief    Sets the width of the light
  @param    light		  light object to set the width of
  @param    angle		  new width of the light
  @return Void

  Sets the width of the light

\-----------------------------------------------------------------------------*/
void SSL_Light_SetWidth(SSL_Light *light, int width) {
	light->width = width;
}


/*!--------------------------------------------------------------------------
  @brief    Sets the range of the light
  @param    light		  light object to set the range of
  @param    angle		  new range of the light
  @return Void

  Sets the range of the light

\-----------------------------------------------------------------------------*/
void SSL_Light_SetRange(SSL_Light *light, int range) {
	light->range = range;
}


/*!--------------------------------------------------------------------------
  @brief    Sets the fade of the light
  @param    light		  light object to set the fade of
  @param    fade		  new fade of the light 1 for fade 0 for no face
  @return Void

  Sets the fade of the light

\-----------------------------------------------------------------------------*/
void SSL_Light_ToggleFade(SSL_Light *light) {
	light->fade = !light->fade;
}


/*!--------------------------------------------------------------------------
  @brief    Sets the brightness of the light
  @param    light		  light object to set the brightness of
  @param    brightness	  new brightness of the light
  @return Void

  Sets the brighness of the light

\-----------------------------------------------------------------------------*/
void SSL_Light_SetBrightness(SSL_Light *light, int brightness) {
	light->brightness = brightness;
}


/*!--------------------------------------------------------------------------
  @brief    Sets the color of the light
  @param    light		  light object to set the color of
  @param    color		  new color of the light
  @return Void

  Sets the color of the light

\-----------------------------------------------------------------------------*/
void SSL_Light_SetColor(SSL_Light *light, SDL_Color color) {
	light->color = color;
}


/*!--------------------------------------------------------------------------
  @brief    Destroy's the light
  @param    light		  light to destroy
  @return Void

  Destroy's the light

\-----------------------------------------------------------------------------*/
void SSL_Light_Destroy(SSL_Light *light) {
	free(light);
}
