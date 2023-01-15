
#include "../Header-Files-Folder/englog-include-file.h"

bool create_fen_string(char* fenString, const Piece board[], State state)
{
	char* strArray[FEN_STRING_PARTS];
	alloc_array_strings(strArray, FEN_STRING_PARTS, 72);

	bool result = create_fen_string_t(fenString, strArray, board, state);

	free_array_strings(strArray, FEN_STRING_PARTS);

	return result;
}

bool create_fen_string_t(char* fenString, char** strArray, const Piece board[], State state)
{
	if(!create_fenstr_parts(strArray, board, state)) return false;

	merge_string_delim(fenString, strArray, FEN_STRING_PARTS, FEN_STRING_DELIM);

	return true;
}

bool create_fenstr_parts(char* strArray[], const Piece board[], State state)
{
	if(!create_string_board(strArray[0], board)) return false;

	if(!create_string_current(strArray[1], state)) return false;

	if(!create_string_castles(strArray[2], state)) return false;

	if(!create_string_passant(strArray[3], state)) return false;

	if(!create_string_clock(strArray[4], state)) return false;

	if(!create_string_turns(strArray[5], state)) return false;

	return true;
}

bool create_string_clock(char* string, State state)
{
	return sprintf(string, "%d", state.clock);
}

bool create_string_turns(char* string, State state)
{
	return sprintf(string, "%d", state.turns);
}

bool create_string_passant(char* string, State state)
{
	Point pawnPoint = passant_pawn_point(state);

	if(pawnPoint != POINT_NONE)
	{
		char passantString[16];
		if(!create_point_string(passantString, pawnPoint)) return false;

		strcat(string, passantString);
	}
	else strcpy(string, FEN_PASSANT_NONE);

	return true;
}

bool create_string_castles(char* string, State state)
{
	if(MASK_WHITE_KSIDE(state.castles)) strncat(string, &(FEN_WKSIDE_SYMBOL), 1);

	if(MASK_WHITE_QSIDE(state.castles)) strncat(string, &(FEN_WQSIDE_SYMBOL), 1);

	if(MASK_BLACK_KSIDE(state.castles)) strncat(string, &(FEN_BKSIDE_SYMBOL), 1);

	if(MASK_BLACK_QSIDE(state.castles)) strncat(string, &(FEN_BQSIDE_SYMBOL), 1);

	if(strlen(string) == 0) strcpy(string, FEN_CASTLES_NONE);

	return true;
}

bool create_string_current(char* string, State state)
{
	if(state.current == TEAM_WHITE) string[0] = WHITE_SYMBOL;

	else if(state.current == TEAM_BLACK) string[0] = BLACK_SYMBOL;

	else return false;

	return true;
}

bool create_string_board(char* string, const Piece board[])
{
	char* strArray[BOARD_RANKS];
	alloc_array_strings(strArray, BOARD_RANKS, BOARD_FILES);

	bool result = create_string_board_t(string, strArray, board);

	free_array_strings(strArray, BOARD_RANKS); return result;
}

bool create_string_board_t(char* string, char** strArray, const Piece board[])
{
	for(int rank = 0; rank < BOARD_RANKS; rank += 1)
		if(!create_board_files(strArray[rank], board, rank)) return false;

	merge_string_delim(string, strArray, BOARD_RANKS, FEN_RANK_DELIM);

	return true;
}

bool create_board_files(char* string, const Piece board[], int rank)
{
	for(int file = 0; file < BOARD_FILES; file += 1)
	{
		Point point = RANK_FILE_POINT(rank, file);

		if(chess_piece_exists(board[point]))
		{
			if(!append_piece_symbol(string, board, point)) return false;
		}
		else if(!append_blank_symbol(string, board, rank, &file)) return false;
	}
	return true;
}

bool append_piece_symbol(char* string, const Piece board[], Point point)
{
	char symbol = chess_piece_symbol(board[point]);

	if(symbol == SYMBOL_NONE) return false;

	strncat(string, &symbol, 1); return true;
}

bool append_blank_symbol(char* string, const Piece board[], int rank, int* file)
{
	char symbol;
	if(!create_blank_symbol(&symbol, rank, file, board)) return false;

	strncat(string, &symbol, 1); return true;
}

bool create_blank_symbol(char* symbol, int rank, int* file, const Piece board[])
{
	int blanks = 0;
	for(; (*file + blanks) < BOARD_FILES; blanks += 1)
	{
		Point point = RANK_FILE_POINT(rank, (*file + blanks));

		if(chess_piece_exists(board[point])) break;
	}
	*file += (blanks - 1); *symbol = (blanks + '0');

	return true;
}

bool create_string_point(char* string, Point point)
{
	if(!POINT_INSIDE_BOARD(point)) return false;

	int rank = POINT_RANK_MACRO(point);
	int file = POINT_FILE_MACRO(point);

	sprintf(string, "%c%c", FILE_SYMBOLS[file], RANK_SYMBOLS[rank]);

	return true;
}

bool create_string_move(char* string, Move move)
{
	if(!move_inside_board(move)) return false;

	char startString[16], stopString[16];

	if(!create_string_point(startString, move.start)) return false;
	if(!create_string_point(stopString, move.stop)) return false;

	if(move_flag_promote(move.flag))
	{
		char pieceSymbol;
		if(!promote_piece_symbol(&pieceSymbol, move)) return false;

		sprintf(string, "%s%s%c", startString, stopString, pieceSymbol);
	}
	else sprintf(string, "%s%s", startString, stopString);

	return true;
}

bool promote_piece_symbol(char* symbol, Move move)
{
	if(move.flag == MFLAG_KNIGHT) *symbol = KNIGHT_PROM_SYMBOL;

	else if(move.flag == MFLAG_BISHOP) *symbol = BISHOP_PROM_SYMBOL;

	else if(move.flag == MFLAG_ROOK) *symbol = ROOK_PROM_SYMBOL;

	else if(move.flag == MFLAG_QUEEN) *symbol = QUEEN_PROM_SYMBOL;

	else return false;

	return true;
}

bool create_point_string(char* pointString, Point point)
{
	if(!POINT_INSIDE_BOARD(point)) return false;

	char fileSymbol = FILE_SYMBOLS[POINT_FILE_MACRO(point)];
	char rankSymbol = RANK_SYMBOLS[POINT_RANK_MACRO(point)];

	sprintf(pointString, "%c%c", fileSymbol, rankSymbol);

	return true;
}
