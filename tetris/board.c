#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "./board.h"

struct Board{
	int height;
	int width;
	char *board;
	int empty;
};

void
board_set_width(struct Board *b, int width)
{
	b->width = width;
}

void
board_set_height(struct Board *b, int height)
{
	b->height = height;
}

int
board_get_width(struct Board *b)
{
	return b->width;
}

int
board_get_height(struct Board *b)
{
	return b->height;
}

int
board_get_size(struct Board *b)
{
	return (board_get_height(b) * board_get_width(b));
}

char *
board_get_board(struct Board *b)
{
	return b->board;
}

int
board_get_empty(struct Board *b)
{
	return b->empty;
}

void
destroy_board(struct Board *b)
{
	free(board_get_board(b));
	free(b);
}

void
show_board(struct Board *b, WINDOW *w)
{
	int height = board_get_height(b);
	int width = board_get_width(b);
	char *board = board_get_board(b);

	for (int y=0; y<height; ++y) {
		for (int x=0; x<width; ++x) {
			/* window is bigger than board by 2 */
			mvwprintw(w,y+1, x+1, "%c", board[y * width + x] );
		}
	}
}

void
board_clear(struct Board *b)
{
	char *p = b->board;
	int n=b->height*b->width;
	while (n) p[n--] = BLANK;
}

struct Board *
new_board(int height, int width)
{
	struct Board *b = malloc(sizeof(struct Board));
	board_set_height(b, height);
	board_set_width(b, width);
	b->board = malloc(sizeof(char) * HEIGHT * HEIGHT);

	// clear board
	board_clear(b);

	b->empty = height * width;
	return b;
}
