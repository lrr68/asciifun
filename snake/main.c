#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "./pixel.h"
#include "./board.h"
#include "./snake.h"

#define FPS 6

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
clear_screen()
{
	printf("\x1b[%dD", WIDTH);
	printf("\x1b[%dA", HEIGHT);
}

void
show_cursor(int show)
{
  if (show)
    fputs("\x1b[?25h", stdout);
  else
    fputs("\x1b[?25l", stdout);
}
void
end_game()
{
	printf("\x1b[%dB", WIDTH);
	printf("\x1b[%dC", HEIGHT);
	printf("GAME OVER\n");
}

int main()
{
	Board *board = new_board(HEIGHT, WIDTH);
	Snake *snake = new_snake(board);
	Direction dir = rand() % COUNT_DIR;
	show_cursor(0);
	place_snake(snake, board);

	do {
		if (!board_get_has_apple(board))
			board_drop_apple(board);

		show_board(board);

		clear_screen();
		move_snake(snake, board, dir);
		usleep(1000 * 1000 / FPS);
	} while (!should_end_game(snake, board));

	destroy_board(board);
	end_game();
	show_cursor(1);

	return 0;
}
