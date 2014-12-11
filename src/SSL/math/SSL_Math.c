/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Math.c
   @author  P. Batty
   @brief   Implements a useful Maths / physics functions

   This module implements useful Math / physics functions
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Math.h"
#include <stdlib.h>
#include <math.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Ray traces between two points
  @param    x0			  Starting x position
  @param    y0			  Starting y postion
  @param	x1			  Ending x positon
  @param	y1			  Ending y positon
  @param	data		  data to pass to the call back function
  @param    func		  Function pointer
  	  	  	  	  	  	  	  @param int	x position currently checking
  	  	  	  	  	  	  	  @param int	y position current checking
  	  	  	  	  	  	  	  @param void	data passe in previously
  	  	  	  	  	  	  	  @return 0 on no collision 1 on collision
  @return 1 if something is in the way else 0

  Scans between the two given points in a strait line calling the function pointer
  with the current x and y coordinates to check, the function should return 1 if the
  x,y point has hit something else 0.

\-----------------------------------------------------------------------------*/
int SSL_Raytrace(int x0, int y0, int x1, int y1, void *data, int(*func)(int, int, void *)) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int x = x0;
    int y = y0;
    int n = 1 + dx + dy;
    int x_inc = (x1 > x0) ? 1 : -1;
    int y_inc = (y1 > y0) ? 1 : -1;
    int error = dx - dy;
    dx *= 2;
    dy *= 2;
    for (; n > 0; --n)
    {
        if(func(x , y, data)) {
        	return(1);
        }
        if (error > 0)
        {
            x += x_inc;
            error -= dy;
        }
        else
        {
            y += y_inc;
            error += dx;
        }
    }

    return(0);
}


/*!--------------------------------------------------------------------------
  @brief    Gets the angle in degrees between two points
  @param    x1			 x1 x point of the first object
  @param	y1			 y1 y point of the first object
  @param	x2			 x2 y point of the second object
  @param	y2			 y2 y point of the second object
  @return Angle in degrees between two points

  Gets the angle in degrees between two points

\-----------------------------------------------------------------------------*/
int SSL_DegreeBetweenPoints(int x1, int y1, int x2, int y2) {
	int deltaX = x1 - x2;
	int deltaY = y1 - y2;
	return atan2(deltaX, -deltaY) * 180 / 3.14159265359;
}


/*!--------------------------------------------------------------------------
  @brief    Converts degrees to radians
  @param    angle		 angle to convert
  @return Degrees to radians

  Converts degrees to radians

\-----------------------------------------------------------------------------*/
double SSL_DegreeToRadians(int angle) {
	return (angle * 3.14159265359) / 180;
}


/*!--------------------------------------------------------------------------
  @brief    Converts Radians to degrees
  @param    radians		 radians to convert
  @return Radians to degrees

  Converts radians to Degrees

\-----------------------------------------------------------------------------*/
int SSL_RadiansToDegree(int radians) {
	return (radians * 180) / 3.14159265359;
}
