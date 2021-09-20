#include <stdlib.h>
#include <stdio.h>

#include "./snake.h"
#include "./board.h"

int
should_end_game(Snake *s, Board *b)
{
	if (snake_get_size(s) == board_get_size(b))
		return 1;
	else if (snake_is_dead(s))
		return 1;
	return 0;
}


int main()
{
	Snake *snake = new_snake(1);
	Board *board = new_board(HEIGHT, WIDTH);

	do {
		board_drop_apple(board);
		show_board(board);

	} while (!should_end_game(snake, board));

	return 0;
}
