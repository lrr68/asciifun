#include <stdlib.h>

struct Pixel {
	int x;
	int y;
};

struct Pixel *
new_pixel(int x, int y)
{
	struct Pixel *p = malloc(sizeof(struct Pixel));
	p->x = x;
	p->y = y;
	return p;
}

void
destroy_pixel(struct Pixel *p)
{
	free(p);
}

int
pixel_get_x(struct Pixel *p)
{
	return p->x;
}

int
pixel_get_y(struct Pixel *p)
{
	return p->y;
}

void
pixel_set_x(struct Pixel *p, int x)
{
	p->x = x;
}

void
pixel_set_y(struct Pixel *p, int y)
{
	p->y = y;
}
