/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Tiled.h
   @author  P. Batty
   @brief   Implements a Tiled .tmx map handler

   This module implements a way to load access and draw .tmx maps
*/
/*--------------------------------------------------------------------------*/

#ifndef SSL_TILED_READER_H_
#define SSL_TILED_READER_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/


#include "../misc/SSL_Hashmap.h"
#include "../misc/SSL_List.h"
#include "../graphics/SSL_Image.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


/*!--------------------------------------------------------------------------
  @brief    SSL_Map

  This object contains information about the map such as size, version ect

\----------------------------------------------------------------------------*/
typedef struct _SSL_MAP_ {
	char *version;						/**< Map version 	 	 	*/
	char *orientation;		   			/**< Map orientation	 	*/
	unsigned int map_width;	   			/**< Map width in tiles  	*/
	unsigned int map_height;			/**< Map height in tiles 	*/
	unsigned int tile_width;			/**< Tile width			 	*/
	unsigned int tile_height;			/**< Tile height		 	*/
	unsigned int total_layers;			/**< Total number of layers */
	SSL_Hashmap *properties;			/**< The map properties 	*/
} SSL_Map;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tile_Layer

  This object contains information about each layer

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tile_Layer_ {
	char *name;
	unsigned int width;
	unsigned int height;
	float opacity;
	char visible;
	int *data;
	SSL_Hashmap *properties;
} SSL_Tile_Layer;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tileset_Info

  This object contains information about the tilesets.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tileset_ {
	unsigned int firstGid;		/**< The id  	      */
	char *name;					/**< The name 	      */
	unsigned int tile_width;	/**< the tile width   */
	unsigned int tile_height;	/**< the tile height  */
	unsigned int spacing;		/**< the tile spacing */
	unsigned int margin;		/**< the tile margin  */
	SSL_Image *image;			/**< the tile image   */
	SSL_Hashmap *properties;	/**< the properties   */
	SSL_List *tiles;			/**< the tiles on set */
} SSL_Tileset;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tile

  This object contains information about the tiles.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tile_ {
	unsigned int id;			/**< The id  	      			   */
	SSL_Image *image;			/**< the image containing the tile */
	SSL_Hashmap *properties;	/**< The properties on this tile   */
} SSL_Tile;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tiled_Map

  The Main object all tiled maps will be made with this object, containing all the
  information on the map stored in it.

  Destroy with SSL_Tiled_Map_Destroy.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tiled_Map_ {
	SSL_Map	 map;					/**<  The map information */
	SSL_List *tilesets;				/**<  The tilesets */
	SSL_List *layers;				/**<  The layers */
} SSL_Tiled_Map;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Loads and creates new Tiled map
  @param    file		 the path to the file
  @param    window       The renderer to use
  @return A SSL_Tiled_Map object

  Loads and creates new Tiled map.
  Destroy with SSL_Tiled_Map_Destroy.

\-----------------------------------------------------------------------------*/
SSL_Tiled_Map *SSL_Tiled_Map_Load(const char *file, SSL_Window *window);


/*!--------------------------------------------------------------------------
  @brief    Draws a loaded map to the screen
  @param    map			 the map to draw
  @param    xOffset		 X Offset to draw the map
  @param    yOffset		 y Offset to draw the map
  @param    window       The window to draw to
  @return A SSL_Tiled_Map object

  Draws the map to the given window.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Draw_Map(SSL_Tiled_Map *map, int xOffset, int yOffset, SSL_Window *window);


/*!--------------------------------------------------------------------------
  @brief    Destroys the map
  @param    map		The map to destroy
  @return   void

  Destroys the map.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Map_Destroy(SSL_Tiled_Map *map);


#endif
