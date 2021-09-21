#ifndef PIXEL_H
#define PIXEL_H

typedef struct Pixel Pixel;

struct Pixel *new_pixel(int x, int y);

void destroy_pixel(struct Pixel *p);
int pixel_get_x(struct Pixel *p);
int pixel_get_y(struct Pixel *p);

#endif
