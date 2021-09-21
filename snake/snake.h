#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_BODY '@'

typedef struct Snake Snake;

typedef enum {
	TOP = -1,
	RIGHT = 2,
	BOTTOM = 1,
	LEFT = -2,
} Direction;

int snake_is_dead(struct Snake *s, Board *b);
int snake_get_size(struct Snake *s);
void snake_set_size(struct Snake *s, int size);
void snake_set_size(struct Snake *s, int size);
struct Snake *new_snake();
Pixel *snake_get_head(struct Snake *s);
Pixel *snake_get_tail(struct Snake *s);
void snake_set_head(struct Snake *s, Pixel *p);
void snake_set_tail(struct Snake *s, Pixel *p);
void place_snake(struct Snake *s, Board *b);

#endif
