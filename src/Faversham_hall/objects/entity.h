#ifndef ENTITY_H_
#define ENTITY_H_

#include "../../SSL/SSL.h"

typedef struct _entity_pos_ {
	int x;
	int y;
	int w;
	int h;
} entity_pos;

typedef struct _entity_image_ {
	SSL_Image *image;
	int max_frames;
	int current_frame;
	long time_frame;
	long next_frame;
} entity_image;

typedef struct _entity_ {
	entity_image image;
	entity_pos pos;
} entity;

#endif
