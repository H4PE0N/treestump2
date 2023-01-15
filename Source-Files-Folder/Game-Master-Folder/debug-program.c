
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
  if(!extract_score_matrixs(TYPE_SCORE_MATRIX)) return false;

	create_hash_matrix(HASH_MATRIX);

	char* fenString = (argc >= 2) ? argv[1] : (char*) FEN_START_STRING;

	Piece* board; State state;
	if(!parse_create_board(&board, &state, fenString, strlen(fenString))) return false;

	Entry* hashTable = create_hash_table(HASH_TABLE_SIZE);



	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
    int file = POINT_FILE_MACRO(point);

		printf("%02d ", point);

		if(file == 7) printf("\n");
	}

	print_console_board(board);

  print_console_state(state);


	Point kingPoint = board_king_point(board, state.current);

	if(kingPoint == POINT_NONE) printf("King Point int NONE\n");

	if(king_inside_check(board, kingPoint)) printf("The king is in check!\n");

	else printf("The king is not in check! team: (%d)\n", state.current);


	long startClock = clock();
	// int seconds = 60;
	int depth = 7;

	Move move;
	engine_depth_move(&move, board, state, hashTable, depth);

	double time = time_passed_since(startClock);

	//printf("depth: (%d) nodes: (%ld) time: (%f)\n", depth, depthNodes, time);

	printf("depth: (%d) time: (%f) move: (%d-%d)\n", depth, time, move.start, move.stop);


	printf("free(hashTable);\n"); free(hashTable);

  printf("free(board);\n"); free(board);

  return false;
}
