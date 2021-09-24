#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "./board.h"
#include "./tiles.h"

#define FPS 5

typedef enum {
	DOWN,
	LEFT,
	RIGHT,
	COUNT_DIR,
} Direction;

/* GLOBAL VARIABLES */
WINDOW *game_w;
Board *board;
Tile *cur_tile;
Direction dir;
int continue_game = 1;

/* FUNCTION DEFINITIONS */
void
show_cursor(int show)
{
  if (show)
	  curs_set(1);
  else
	  curs_set(0);
}

WINDOW *
create_new_win(int height, int width, int start_y, int start_x)
{
	WINDOW *local_win;

	local_win = newwin(height, width, start_y, start_x);

	/* use default caracters for borders */
	box(local_win, 0 , 0);
	wrefresh(local_win);

	return local_win;
}

void *
get_cmd_thread()
{
	int c;
	while (1) {
		c = wgetch(game_w);

		show_or_hide_tile(cur_tile, board, 0);
		switch (c) {
			case 'k':
			case 'j':
				rotate_tile(cur_tile);
				break;
			case 'l':
				move_tile(cur_tile, board, 1);
				break;
			case 'h':
				move_tile(cur_tile, board, -1);
				break;
			case 'q':
				continue_game = 0;
				break;
		}
		show_or_hide_tile(cur_tile, board, 1);
	}
}

void
init_game(Board *b, Tile *t)
{
	/* start ncurses     */
	if (initscr() == NULL) {
		perror(strerror(errno));
		exit(errno);
	}

	raw();
	noecho();
	show_cursor(0);
	show_or_hide_tile(t, b, 1);
}

void
housekeeping(Board *b, Tile *s, WINDOW *w)
{
	delwin(w);
	destroy_board(b);
	destroy_tile(s);
	show_cursor(1);
	echo();
	endwin();
}

int main()
{
	srand(time(NULL));
	board = new_board(HEIGHT, WIDTH);
	TileType type = random_tiletype();
	cur_tile = new_tile(type);
	pthread_t cmd_thread_id;

	init_game(board, cur_tile);
	game_w = create_new_win(HEIGHT+2, WIDTH+2, 0, 0);
	pthread_create(&cmd_thread_id, NULL, get_cmd_thread, NULL);

	do {
		wrefresh(game_w);
		show_board(board, game_w);
		lower_tile(cur_tile, board);
		doupdate();

		usleep(1000000/ FPS);
	} while (continue_game && board_get_empty(board) > 0);

	housekeeping(board, cur_tile, game_w);
	pthread_kill(cmd_thread_id, SIGINT);

	return 0;
}
