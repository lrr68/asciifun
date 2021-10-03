#include <ncurses.h>
#include <stdlib.h>

#include "./board.h"
#include "./tiles.h"

struct Tile {
	int positions[TILESIZE];
	TileType type;
};

struct Tile *
new_tile(TileType p)
{
	int x = WIDTH/2;
	struct Tile *t = malloc(sizeof(struct Tile));
	t->type = p;

	switch (p) {
		case TILE_T:
			t->positions[0] = x;
			t->positions[1] = WIDTH+x-1;
			t->positions[2] = WIDTH+x;
			t->positions[3] = WIDTH+x+1;
			break;
		case TILE_I:
			t->positions[0] = x;
			t->positions[1] = x-1;
			t->positions[2] = x+1;
			t->positions[3] = x+2;
			break;
		case TILE_LR:
			t->positions[0] = x;
			t->positions[1] = WIDTH+x-1;
			t->positions[2] = x-1;
			t->positions[3] = x+1;
			break;
		case TILE_LL:
			t->positions[0] = x;
			t->positions[1] = x-1;
			t->positions[2] = x+1;
			t->positions[3] = WIDTH+x+1;
			break;
		case TILE_SQ:
			t->positions[0] = x;
			t->positions[1] = WIDTH+x;
			t->positions[2] = x+1;
			t->positions[3] = WIDTH+x+1;
			break;
		case TILE_ZR:
			t->positions[0] = x-1;
			t->positions[1] = WIDTH+x;
			t->positions[2] = x;
			t->positions[3] = WIDTH+x+1;
			break;
		case TILE_ZL:
			t->positions[0] = x;
			t->positions[1] = x+1;
			t->positions[2] = WIDTH+x;
			t->positions[3] = WIDTH+x-1;
			break;
		default:
			break;
	}

	return t;
}

TileType
random_tiletype()
{
	return (TileType) rand() % COUNT_TILE;
}

void
destroy_tile(struct Tile *t)
{
	free(t);
}

/* true if pos (position in board) is in cur_tile */
int
is_tile(struct Tile *t, int pos)
{
	int is_tile = 0;
	for (int i=0; i<TILESIZE && !is_tile; ++i) {
		if (t->positions[i] == pos)
			is_tile=1;
	}

	return is_tile;
}

void
move_tile(struct Tile *t, Board *b, int offset)
{
	char *board = board_get_board(b);
	int can_move = 1;
	int row;

	if (offset != WIDTH) {
		for (int i=0; i<TILESIZE; ++i) {
			row = t->positions[i] / WIDTH;

			/* moving outside of current row */
			if (t->positions[i] + offset < (row * WIDTH)
					|| t->positions[i] + offset > row * WIDTH + WIDTH - 1) {
				can_move = 0;
				break;
			}

			/* moving to the sides, must check if there is another piece set */
			if (offset < WIDTH && board[t->positions[i] + offset] != BLANK
					&& !is_tile(t, t->positions[i] + offset)) {
				can_move = 0;
				break;
			}
		}
	} else {
		for (int i=0; i<TILESIZE; ++i) {
			if (t->positions[i] + offset > WIDTH * HEIGHT) {
				can_move = 0;
				break;
			}
		}
	}

	if (can_move) {
		for (int i=0; i<TILESIZE; ++i) {
			t->positions[i]+=offset;
		}
	}
}

void
lower_tile(struct Tile *t, Board *b)
{
	int may_move = 1;
	char *board = board_get_board(b);

	/* check if position bellow is empty */
	for (int i=0; i<TILESIZE; ++i) {
		/* May move if board below is blank or is tile */
		if (board[t->positions[i] + WIDTH] != BLANK
				&& !is_tile(t, t->positions[i] + WIDTH)) {
			may_move = 0;
			break;
		}
	}

	if (may_move) {
		show_or_hide_tile(t, b, 0);
		move_tile(t, b, WIDTH);
		show_or_hide_tile(t, b, 1);
	} else {
		destroy_tile(t);
		cur_tile = new_tile(random_tiletype());
	}
}

void
show_or_hide_tile(struct Tile *t, Board *b, int show)
{
	char c = BLANK;
	if (show)
		c = SET;

	char *board = board_get_board(b);
	for (int i=0; i<TILESIZE; ++i) {
		board[t->positions[i]] = c;
	}
}

void
rotate_tile(struct Tile *t, Board *b)
{
	char *board = board_get_board(b);
	int new_positions[TILESIZE] = {0};
	switch (t->type) {
		case TILE_T:
			t->positions[0] = 0;
			t->positions[1] = WIDTH+0-1;
			t->positions[2] = WIDTH+0;
			t->positions[3] = WIDTH+0+1;
			break;
		case TILE_I:
			t->positions[0] = 0;
			t->positions[1] = 0-1;
			t->positions[2] = 0+1;
			t->positions[3] = 0+2;
			break;
		case TILE_LR:
			t->positions[0] = 0;
			t->positions[1] = WIDTH+0-1;
			t->positions[2] = 0-1;
			t->positions[3] = 0+1;
			break;
		case TILE_LL:
			t->positions[0] = 0;
			t->positions[1] = 0-1;
			t->positions[2] = 0+1;
			t->positions[3] = WIDTH+0+1;
			break;
		case TILE_SQ:
			t->positions[0] = 0;
			t->positions[1] = WIDTH+0;
			t->positions[2] = 0+1;
			t->positions[3] = WIDTH+0+1;
			break;
		case TILE_ZR:
			t->positions[0] = 0-1;
			t->positions[1] = WIDTH+0;
			t->positions[2] = 0;
			t->positions[3] = WIDTH+0+1;
			break;
		case TILE_ZL:
			t->positions[0] = 0;
			t->positions[1] = 0+1;
			t->positions[2] = WIDTH+0;
			t->positions[3] = WIDTH+0-1;
			break;
		default:
			break;
	}
}
