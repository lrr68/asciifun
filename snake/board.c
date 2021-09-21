#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "./board.h"

struct Board{
	int height;
	int width;
	char *board;
	int *empty_spaces;
	int has_apple;
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

int *
board_get_empty_spaces(struct Board *b)
{
	return b->empty_spaces;
}

void
destroy_board(struct Board *b)
{
	free(board_get_board(b));
	free(board_get_empty_spaces(b));
	free(b);
}

void
show_board(struct Board *b)
{
	int height = board_get_height(b);
	int width = board_get_width(b);
	char *board = board_get_board(b);

	for (int y=0; y<height; ++y) {
		for (int x=0; x<width; ++x) {
			/* print board limits */
			if ((x==0 && y==0) || (x==width-1 && y==height-1)
					|| (x==width-1 && y==0) || (x==0 && y==height-1)) {
				printf(" %c", BOARD_CORNER);
			} else if (y == 0 || y == height-1) {
				printf(" %c", BOARD_LIMIT_H);
			} else if (x == 0 || x == width-1) {
				printf(" %c", BOARD_LIMIT_V);
			} else {
				printf(" %c", board[y * width + x]);
			}
		}
		printf("\n");
	}
}

void
board_drop_apple(struct Board *b)
{
	char *board = board_get_board(b);
	srand(time(NULL));
	int r = rand() % (board_get_width(b) * board_get_height(b));
	int apple_dropped = 0;

	while (!apple_dropped) {
		if (board[r] == BLANK) {
			board[r] = APPLE;
			apple_dropped = 1;
		} else {
			r = rand() % (board_get_width(b) * board_get_height(b));
		}
	}
	board_set_has_apple(b, 1);
}

int
board_get_has_apple(struct Board *b)
{
	return b->has_apple;
}

void
board_set_has_apple(struct Board *b, int a)
{
	b->has_apple = a;
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
	b->board = malloc(sizeof(char) * height * width);

	// clear board
	board_clear(b);

	b->empty_spaces = malloc(sizeof(char) * height * width);
	return b;
}
