#include <stdlib.h>

#include "./pixel.h"
#include "./board.h"
#include "./snake.h"

struct Snake{
	int size;
	int dead;
	Pixel *head;
	Pixel *tail;
};

int
snake_is_dead(struct Snake *s, Board *b)
{
	if (pixel_get_x(s->head) == 0 || pixel_get_x(s->head) == board_get_width(b)-1
			|| pixel_get_y(s->head) == 0 || pixel_get_y(s->head) == board_get_height(b)-1)
		s->dead = 1;
	return s->dead;
}

void
place_snake(struct Snake *s, Board *b)
{
	char *board = board_get_board(b);
	board[pixel_get_y(s->head) * board_get_width(b) + pixel_get_x(s->head)] = SNAKE_BODY;
}

int
snake_get_size(struct Snake *s)
{
	return s->size;
}

void
snake_set_size(struct Snake *s, int size)
{
	s->size = size;
}

Pixel *
snake_get_head(struct Snake *s)
{
	return s->head;
}

Pixel *
snake_get_tail(struct Snake *s)
{
	return s->tail;
}

void
snake_set_head(struct Snake *s, Pixel *p)
{
	s->head = p;
}

void
snake_set_tail(struct Snake *s, Pixel *p)
{
	s->tail = p;
}

struct Snake *
new_snake()
{
	Pixel *p = new_pixel(1,1);
	struct Snake *s = malloc(sizeof(struct Snake));
	snake_set_size(s, 1);
	s->dead = 0;
	snake_set_head(s, p);
	snake_set_tail(s, p);
	return s;
}
