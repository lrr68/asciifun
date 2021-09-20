#ifndef SNAKE_H
#define SNAKE_H

typedef struct Snake Snake;

int snake_is_dead(struct Snake *s);
int snake_get_size(struct Snake *s);
void snake_set_size(struct Snake *s, int size);
void snake_set_size(struct Snake *s, int size);
void kill_snake(struct Snake *s);
struct Snake *new_snake(int size);

#endif
