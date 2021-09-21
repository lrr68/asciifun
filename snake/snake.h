#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_BODY '@'

typedef struct Snake Snake;

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	COUNT_DIR,
} Direction;

void destroy_snake(struct Snake *s);
int snake_is_dead(struct Snake *s, Board *b);
int snake_get_size(struct Snake *s);
void snake_set_size(struct Snake *s, int size);
void snake_set_size(struct Snake *s, int size);
struct Snake *new_snake(struct Board *b);
Pixel *snake_get_head(struct Snake *s);
Pixel *snake_get_tail(struct Snake *s);
void snake_set_head(struct Snake *s, Pixel *p);
void snake_set_tail(struct Snake *s, Pixel *p);
void place_snake(struct Snake *s, Board *b);
void move_snake(struct Snake *s, Board *b, Direction d);

#endif
