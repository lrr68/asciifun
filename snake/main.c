#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "./pixel.h"
#include "./board.h"
#include "./snake.h"

#define FPS 10
#define CURSOR_TO_TOP      "\x1b[%dA"
#define CURSOR_TO_RIGHT    "\x1b[%dB"
#define CURSOR_TO_BOTTOM   "\x1b[%dC"
#define CURSOR_TO_LEFT     "\x1b[%dD"
#define HIDE_CURSOR        "\x1b[?25l"
#define SHOW_CURSOR        "\x1b[?25h"

/* GLOBAL VARIABLES */
Direction dir;
WINDOW *game_w;

/* FUNCTION DEFINITIONS */
int
should_end_game(Snake *s, Board *b)
{
	if (snake_get_size(s) == board_get_size(b))
		return 1;
	else if (snake_is_dead(s, b))
		return 1;
	return 0;
}

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

void
end_game()
{
	printf(CURSOR_TO_RIGHT, WIDTH);
	printf(CURSOR_TO_BOTTOM, HEIGHT);
	printf("GAME OVER\n");
}

void *
get_cmd_thread()
{
	int c;
	while (1) {
		c = wgetch(game_w);

		switch (c) {
			case 'h':
				dir = LEFT;
				break;
			case 'j':
				dir = DOWN;
				break;
			case 'k':
				dir = UP;
				break;
			case 'l':
				dir = RIGHT;
				break;
			case 'q':
				dir = COUNT_DIR;
		}
	}
}

void
init_game(Board *b, Snake *s)
{
	/* start ncurses     */
	if (initscr() == NULL) {
		perror(strerror(errno));
		exit(errno);
	}

	raw();
	noecho();
	show_cursor(0);
	place_snake(s, b);
}

void
housekeeping(Board *b, Snake *s)
{
	destroy_board(b);
	destroy_snake(s);
	end_game();
	show_cursor(1);
	echo();
	endwin();
}

int main()
{
	srand(time(NULL));
	dir = rand() % COUNT_DIR;
	Board *board = new_board(HEIGHT, WIDTH);
	Snake *snake = new_snake(board);
	pthread_t cmd_thread_id;

	init_game(board, snake);
	game_w = create_new_win(HEIGHT+2, WIDTH+2, 0, 0);
	pthread_create(&cmd_thread_id, NULL, get_cmd_thread, NULL);

	do {
		wrefresh(game_w);

		if (!board_get_has_apple(board))
			board_drop_apple(board);

		show_board(board, game_w);
		doupdate();
		move_snake(snake, board, dir);

		/* terminal ratio makes movement on y be 2x faster */
		if (dir == UP || dir == DOWN)
			usleep(2000000/ FPS);
		else
			usleep(1000000/ FPS);
	} while (!should_end_game(snake, board));

	housekeeping(board, snake);
	pthread_kill(cmd_thread_id, SIGINT);

	return 0;
}
