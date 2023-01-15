
#include "../Engine-Logic-Folder/Header-Files-Folder/englog-include-file.h"
#include "../Chess-Engine-Folder/Header-Files-Folder/engine-include-file.h"
#include "../Game-Console-Folder/Header-Files-Folder/console-include-file.h"

bool print_console_board(const Piece board[])
{
	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		int rank = POINT_RANK_MACRO(point);
    int file = POINT_FILE_MACRO(point);

		if(file == 0) printf("%d ", (BOARD_RANKS - rank));

    char symbol = chess_piece_symbol(board[point]);

		if(symbol == SYMBOL_NONE) printf("  ");

		else printf("%c ", symbol);

  	if(file == 7) printf("\n");
	}
  printf("  A B C D E F G H\n"); return true;
}

bool print_console_state(State state)
{
	printf("current:(%s)\n", TEAM_WORDS[state.current]);

	printf("turns:(%d)\n", state.turns);

	printf("clock:(%d)\n", state.clock);

	return true;
}

int main(int argc, char* argv[])
{
  char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

  Piece* board; State state;
	if(!parse_create_board(&board, &state, fenString, strlen(fenString)))
  {
    printf("error parse_create_board\n");

    return false;
  }

	print_console_board(board);

  print_console_state(state);

  printf("free(board);\n"); free(board);

  return false;
}
