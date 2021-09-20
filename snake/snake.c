#include <stdlib.h>

#include "./pixel.h"

struct Snake{
	int size;
	int dead;
	Pixel head;
	Pixel tail;
};

int
snake_is_dead(struct Snake *s)
{
	return s->dead;
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

void
kill_snake(struct Snake *s)
{
	s->dead = 1;
}

struct Snake *
new_snake(int size)
{
	struct Snake *s = malloc(sizeof(struct Snake));
	snake_set_size(s, size);
	snake_set_head(*(new_pixel(0,0)));
	return s;
}
