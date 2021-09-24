#ifndef BOARD_H
#define BOARD_H

#define HEIGHT 20
#define WIDTH  10

#define BOARD_CORNER '+'
#define BOARD_LIMIT_H '-'
#define BOARD_LIMIT_V '|'

#define BLANK ' '
#define SET   '@'

typedef struct Board Board;

void board_set_width(struct Board *b, int width);
void board_set_height(struct Board *b, int height);
int board_get_width(struct Board *b);
int board_get_height(struct Board *b);
int board_get_size(struct Board *b);
char *board_get_board(struct Board *b);
void destroy_board(struct Board *b);
void show_board(struct Board *b, WINDOW *w);
void board_clear(struct Board *b);
int board_get_empty(struct Board *b);
struct Board *new_board(int height, int width);

#endif
