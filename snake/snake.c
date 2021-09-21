#include <time.h>
#include <stdlib.h>

#include "./pixel.h"
#include "./board.h"
#include "./snake.h"

struct Snake{
	int size;
	int dead;
	Pixel *body[HEIGHT * WIDTH + 1];/* one extra position to always be able to shift */
};

void
destroy_snake(struct Snake *s)
{
	for (int i=0; i<s->size; ++i) {
		free(s->body[i]);
	}
	free(s);
}

void
grow_snake(struct Snake *s)
{
	snake_set_size(s, snake_get_size(s) + 1);
}

int
snake_is_dead(struct Snake *s, Board *b)
{
	if (pixel_get_x(snake_get_head(s)) == 0 || pixel_get_x(snake_get_head(s)) == board_get_width(b)-1
			|| pixel_get_y(snake_get_head(s)) == 0 || pixel_get_y(snake_get_head(s)) == board_get_height(b)-1)
		s->dead = 1;
	return s->dead;
}

void
place_snake(struct Snake *s, Board *b)
{
	char *board = board_get_board(b);
	board[pixel_get_y(snake_get_head(s)) * board_get_width(b) + pixel_get_x(snake_get_head(s))] = SNAKE_BODY;
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
	return s->body[0];
}

Pixel *
snake_get_tail(struct Snake *s)
{
	return s->body[snake_get_size(s)-1];
}

void
snake_set_head(struct Snake *s, Pixel *p)
{
	s->body[0] = p;
}

void
snake_set_tail(struct Snake *s, Pixel *p)
{
	s->body[snake_get_size(s)-1] = p;
}


 /* this emulates the movement of the snake by
  * shifting the body array to free the head position,
  * removing the tail and creating a new head in the new
  * direction
  */
void
move_snake(struct Snake *s, Board *b, Direction d)
{
	char *board = board_get_board(b);
	int width = board_get_width(b);
	int size = snake_get_size(s);
	int grow = 0;
	int dx = 0;
	int dy = 0;
	Pixel *new_head;
	Pixel *old_head = snake_get_head(s);
	Pixel *tail = snake_get_tail(s);

	/* shift array */
	for (int i=size; i>0; --i) {
		s->body[i] = s->body[i-1];
	}

	/* create new head */
	switch(d) {
		case UP:
			dy = -1;
			break;
		case DOWN:
			dy = +1;
			break;
		case LEFT:
			dx = -1;
			break;
		case RIGHT:
			dx = +1;
			break;
		default: //nothing to do
			break;
	}
	new_head = new_pixel(pixel_get_x(old_head) + dx, pixel_get_y(old_head) + dy);
	snake_set_head(s, new_head);

	/* ate apple? */
	if (board[pixel_get_y(new_head) * width + pixel_get_x(new_head)] == APPLE) {
		grow = 1;
		board_set_has_apple(b, 0);
	}

	/* move head */
	board[pixel_get_y(new_head) * width + pixel_get_x(new_head)] = SNAKE_BODY;

	/* remove tail if snake didn't grow */
	if (grow) {
		grow_snake(s);
	} else {
		board[pixel_get_y(tail) * board_get_width(b) + pixel_get_x(tail)] = BLANK;
	}
}

struct Snake *
new_snake(struct Board *b)
{
	int x,y;
	char *board = board_get_board(b);
	int width = board_get_width(b);
	int height = board_get_height(b);

	/* snake stars at random position */
	srand(time(NULL));
	do {
		x = (rand() %  (width/2)) + width/4;
 		y = (rand() % (height/2)) + height/4;
	} while (board[y*width + x] != BLANK);

	struct Snake *s = malloc(sizeof(struct Snake));
	snake_set_size(s, 1);
	snake_set_head(s, new_pixel(x,y));
	s->dead = 0;
	return s;
}
