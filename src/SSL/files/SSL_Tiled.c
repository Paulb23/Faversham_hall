/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Tiled.c
   @author  P. Batty
   @brief   Implements a Tiled .tmx map handler

   This module implements a way to load access and draw .tmx maps
*/
/*--------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Tiled.h"
#include "../SSL_Settings.h"
#include "../misc/SSL_Hashmap.h"
#include "../graphics/SSL_Image.h"
#include "../misc/SSL_List.h"
#include "../misc/SSL_Logger.h"
#include "../misc/SSL_String.h"

#include "../graphics/SSL_Window.h"
#include <stdlib.h>
#include <string.h>
#include "mxml/mxml.h"
#include "base64.h"
#include "zlib.h"
#include "zconf.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static SSL_Tiled_Map *SSL_Tiled_Map_Create() {
	SSL_Tiled_Map *map = malloc(sizeof(SSL_Tiled_Map));

	if (!map) {
		SSL_Log_Write("Failed to allocate memory for new map!");
		free(map);
		return 0;
	}

	map->map.properties = SSL_Hashmap_Create();
	map->layers = SSL_List_Create();
	map->tilesets = SSL_List_Create();

	return map;
}

static void map_properties_handler(mxml_node_t *node, SSL_Tiled_Map *map) {
		map->map.version = mxmlElementGetAttr(node, "version");
		map->map.orientation = mxmlElementGetAttr(node, "orientation");
		map->map.map_width = atoi(mxmlElementGetAttr(node, "width"));
		map->map.map_height = atoi(mxmlElementGetAttr(node, "height"));
		map->map.tile_width = atoi(mxmlElementGetAttr(node, "tilewidth"));
		map->map.tile_height = atoi(mxmlElementGetAttr(node, "tileheight"));
		map->map.total_layers = 0;

		// load properties function
}

static void map_tileset_handeler(mxml_node_t *node, SSL_Tiled_Map *map, char *filePath, SSL_Window *window) {
		SSL_Tileset *tileset = malloc(sizeof(SSL_Tileset));

		if(!tileset) {
			SSL_Log_Write("ERROR: Unable to create memory for tileset! ");
			return;
		}

		tileset->firstGid = atoi(mxmlElementGetAttr(node, "firstgid"));
		tileset->name = mxmlElementGetAttr(node, "name");
		tileset->tile_width = atoi(mxmlElementGetAttr(node, "tilewidth"));
		tileset->tile_height = atoi(mxmlElementGetAttr(node, "tileheight"));
		tileset->spacing = atoi(mxmlElementGetAttr(node, "spacing"));
		tileset->margin = atoi(mxmlElementGetAttr(node, "margin"));

		// TODO: Get size of for allocation
		char path[9999];
		sprintf(path, "%s%s", filePath, mxmlElementGetAttr(node->child->next, "source"));
		tileset->image =  SSL_Image_Load(path, map->map.tile_width,map->map.tile_height, window);

		tileset->tiles = SSL_List_Create();
		tileset->properties = SSL_Hashmap_Create();

		//load properties function

		SSL_List_Add(map->tilesets, tileset);
}

static void map_tile_layer_handeler(mxml_node_t *node, SSL_Tiled_Map *map) {
	SSL_Tile_Layer *layer = malloc(sizeof(SSL_Tile_Layer));

	if(!layer) {
		SSL_Log_Write("ERROR: Unable to create memory for map layer! ");
		return;
	}

	layer->name = mxmlElementGetAttr(node, "name");
	layer->width = atoi(mxmlElementGetAttr(node, "width"));
	layer->height = atoi(mxmlElementGetAttr(node, "height"));
	layer->opacity = atoi(mxmlElementGetAttr(node, "opacity"));

	if(mxmlElementGetAttr(node, "visible") == NULL) {
		layer->visible = 1;
	} else {
		layer->visible = 0;
	}

	mxml_node_t *data;
	data = mxmlFindElement(node, node, "data", NULL, NULL, MXML_DESCEND);

	//TODO: Get size of allocation
	char base64DecodeOutput[9999];
	b64_decode((char *)mxmlGetText(data, 0), base64DecodeOutput);

	int *tile_map = malloc(map->map.map_width * map->map.map_height * 4);

	 uLongf outlen = map->map.map_width * map->map.map_height * 4;
	 uncompress((Bytef *)tile_map, &outlen, (const Bytef *)base64DecodeOutput, strlen(base64DecodeOutput));

	layer->data = tile_map;

	layer->properties = SSL_Hashmap_Create();

	// load tile properties

	SSL_List_Add(map->layers, layer);
	map->map.total_layers++;
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/


/*!--------------------------------------------------------------------------
  @brief    Loads and creates new Tiled map
  @param    file		 the path to the file
  @param    window       The renderer to use
  @return A SSL_Tiled_Map object

  Loads and creates new Tiled map.
  Destroy with SSL_Tiled_Map_Destroy.

\-----------------------------------------------------------------------------*/
SSL_Tiled_Map *SSL_Tiled_Map_Load(const char *file,  SSL_Window *window) {

	/* create the map */
	SSL_Tiled_Map *map = SSL_Tiled_Map_Create();
	if(map == 0) {
		return 0;
	}

	/* open the file */
	FILE *fp = fopen(file, "r");
	if (fp == NULL) {
		SSL_Log_Write("Failed to find file!");
		SSL_Tiled_Map_Destroy(map);
		return 0;
	}

	mxml_node_t *tree, *node;
	tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK );
	fclose(fp);

	if (!tree) {
		SSL_Log_Write("Failed to find file!");
		SSL_Tiled_Map_Destroy(map);
		return 0;
	}

	/* load the map properties */
	node = mxmlFindElement(tree, tree, "map", NULL, NULL, MXML_DESCEND);
	map_properties_handler(node, map);
	tree = node;

	while (node != NULL) {
		if ( mxmlGetType(node) == MXML_ELEMENT) {

			 if (!strcmp(node->value.element.name, "tileset")) {
				 map_tileset_handeler(node, map, SSL_String_Substring(file, 0, SSL_String_Last_Index_Of(file, "/")), window);
		      } else if (!strcmp(node->value.element.name, "layer")) {
			 	  map_tile_layer_handeler(node, map);
		      }
		}
		mxml_node_t* next = mxmlGetFirstChild(node);
		if ( next != NULL ) {
		      node = next;
		} else {
		    next = mxmlGetNextSibling(node);
		    if ( next != NULL ) {
		    	node = next;
			} else {
				next = mxmlGetNextSibling(node->parent);
				if( next != NULL) {
					node = next;
				} else {
					node = mxmlGetNextSibling(tree);
					tree = node;
				}
			}
		}
	}

	return map;
}


/*!--------------------------------------------------------------------------
  @brief    Draws a loaded map to the screen
  @param    map			 the map to draw
  @param    xOffset		 X Offset to draw the map
  @param    yOffset		 y Offset to draw the map
  @param    window       The window to draw to
  @return A SSL_Tiled_Map object

  Draws the map to the given window.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Draw_Map(SSL_Tiled_Map *map, int xOffset, int yOffset, SSL_Window *window) {

	int layer = 1;
	int *tiles;

	int i, j;
	while (layer <= map->map.total_layers) {
		SSL_Tile_Layer *tile_layer = SSL_List_Get(map->layers, layer);

		if (tile_layer->visible != 0) {

			tiles = tile_layer->data;
			for (i = 0; i < map->map.map_width; i++) {
				for (j = 0; j < map->map.map_height; j++) {
					if (tiles[map->map.map_width * j + i] != 0) {

						 SSL_Tileset *tileset;
						 int k;
						 for (k = 1; k < SSL_List_Size(map->tilesets); k++) {
							 tileset = SSL_List_Get(map->tilesets, k+1);
							 if (tiles[map->map.map_width * j + i] < tileset->firstGid || tileset == NULL) {
								 tileset = SSL_List_Get(map->tilesets, k);
								 break;
							 }
						 }
						 int frame = 1;

						 if (k != 1) {
							 frame = tiles[map->map.map_width * j + i] - (tileset->firstGid - 1);
						 } else {
							 frame = tiles[map->map.map_width * j + i];
						 }
						 SSL_Image_Draw(tileset->image, i * map->map.tile_width + xOffset, j*map->map.tile_height + yOffset,0,frame ,SDL_FLIP_NONE, window);
					}
				}
			}
		}
		layer++;
	}
}


/*!--------------------------------------------------------------------------
  @brief    Destroys the map
  @param    map		The map to destroy
  @return   void

  Destroys the map.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Map_Destroy(SSL_Tiled_Map *map) {
	SSL_Hashmap_Destroy(map->map.properties);
	SSL_List_Destroy(map->layers);
	SSL_List_Destroy(map->tilesets);
}
