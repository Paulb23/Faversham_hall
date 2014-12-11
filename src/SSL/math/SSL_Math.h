/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Math.h
   @author  P. Batty
   @brief   Implements a useful Maths / physics functions

   This module implements useful Math / physics functions
*/
/*--------------------------------------------------------------------------*/

#ifndef SSL_MATH_H_
#define SSL_MATH_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
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
int SSL_Raytrace(int x0, int y0, int x1, int y1, void *data, int(*func)(int, int, void *));


/*!--------------------------------------------------------------------------
  @brief    Gets the angle in degrees between two points
  @param    x1			 x1 x point of the first object
  @param	y1			 y1 y point of the first object
  @param	x2			 x2 y point of the second object
  @param	y2			 y2 y point of the second object
  @return Void

  Gets the angle in degrees between two points

\-----------------------------------------------------------------------------*/
int SSL_DegreeBetweenPoints(int x1, int y1, int x2, int y2);


/*!--------------------------------------------------------------------------
  @brief    Converts degrees to radians
  @param    angle		 angle to convert
  @return Degrees to radians

  Converts degrees to radians

\-----------------------------------------------------------------------------*/
double SSL_DegreeToRadians(int angle);


/*!--------------------------------------------------------------------------
  @brief    Converts Radians to degrees
  @param    radians		 radians to convert
  @return Radians to degrees

  Converts radians to Degrees

\-----------------------------------------------------------------------------*/
int SSL_RadiansToDegree(int radians);

#endif
