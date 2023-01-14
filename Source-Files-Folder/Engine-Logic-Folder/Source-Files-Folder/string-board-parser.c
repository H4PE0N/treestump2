
#include "../Header-Files-Folder/englog-include-file.h"

bool parse_create_board(Piece** board, State* state, const char fenString[], int strLength)
{
  *board = malloc(sizeof(Piece) * BOARD_POINTS);

  if(parse_fen_string(*board, state, fenString, strLength)) return true;

  free(*board); return false;
}

bool parse_fen_string(Piece* board, State* state, const char fenString[], int strLength)
{
  char* strArray[FEN_STRING_PARTS];
  if(!split_string_delim(strArray, fenString, strLength, FEN_STRING_DELIM, FEN_STRING_PARTS)) return false;

  bool result = parse_string_array(board, state, strArray);

  free_array_strings(strArray, FEN_STRING_PARTS); return result;
}

bool parse_string_array(Piece* board, State* state, char* strArray[])
{
  if(!parse_string_board(board, strArray[0], strlen(strArray[0]))) return false;

  return parse_string_state(state, strArray);
}

bool parse_string_state(State* state, char* strArray[])
{
  if(!parse_string_current(state, strArray[1], strlen(strArray[1]))) return false;

	if(!parse_string_castles(state, strArray[2], strlen(strArray[2]))) return false;

	if(!parse_string_passant(state, strArray[3], strlen(strArray[3]))) return false;

	if(!parse_string_clock(state, strArray[4], strlen(strArray[4]))) return false;

	if(!parse_string_turns(state, strArray[5], strlen(strArray[5]))) return false;

	return true;
}

bool parse_string_current(State* state, const char strToken[], int strLength)
{
  if(strLength != 1) return false;

  if(strToken[0] == WHITE_SYMBOL) state->current = TEAM_WHITE;

  else if(strToken[0] == BLACK_SYMBOL) state->current = TEAM_BLACK;

  else return false;

  return true;
}

bool parse_string_clock(State* state, const char strToken[], int strLength)
{
	int clock = atoi(strToken);

	if((clock == 0) && (strToken[0] != '0')) return false;

	state->clock = clock; return true;
}

bool parse_string_turns(State* state, const char strToken[], int strLength)
{
	int turns = atoi(strToken);

	if((turns == 0) && (strToken[0] != '0')) return false;

	state->turns = turns; return true;
}

bool parse_string_passant(State* state, const char strToken[], int strLength)
{
	if(!strcmp(strToken, FEN_PASSANT_NONE)) return true;

	Point passantPoint = POINT_NONE;
	if(!parse_string_point(&passantPoint, strToken, strLength)) return false;

	state->passant = (POINT_FILE_MACRO(passantPoint) + 1);

	return true;
}

bool parse_string_point(Point* point, const char string[], int strLength)
{
	if(strLength != 2) return false;

  int file = string_symbol_index(FILE_SYMBOLS, BOARD_FILES, string[0]);

	int rank = string_symbol_index(RANK_SYMBOLS, BOARD_RANKS, string[1]);

	if((file == INDEX_NONE) || (rank == INDEX_NONE)) return false;

	*point = RANK_FILE_POINT(rank, file); return true;
}

bool parse_string_castles(State* state, const char strToken[], int strLength)
{
	if(!strcmp(strToken, FEN_CASTLES_NONE)) return true;

	if(strLength > FEN_MAX_CASTLES) return false;

  int castle = EMPTY_CASTLE;

	for(int index = 0; index < strLength; index += 1)
	{
		if(!parse_castle_symbol(&castle, strToken[index])) return false;
	}
	state->castle = castle; return true;
}

bool parse_castle_symbol(int* castle, char symbol)
{
  if(symbol == FEN_WKSIDE_SYMBOL) *castle |= WHITE_KSIDE;

  else if(symbol == FEN_WQSIDE_SYMBOL) *castle |= WHITE_QSIDE;

  else if(symbol == FEN_BKSIDE_SYMBOL) *castle |= BLACK_KSIDE;

  else if(symbol == FEN_BQSIDE_SYMBOL) *castle |= BLACK_QSIDE;

  else return false;

  return true;
}

bool parse_string_board(Piece* board, const char strToken[], int strLength)
{
  char* strArray[BOARD_RANKS];
	if(!split_string_delim(strArray, strToken, strLength, FEN_RANK_DELIM, BOARD_RANKS)) return false;

  bool result = parse_board_ranks(board, strArray);

  free_array_strings(strArray, BOARD_RANKS); return result;
}

bool parse_board_ranks(Piece* board, char* strArray[])
{
  for(int rank = 0; rank < BOARD_RANKS; rank += 1)
  {
    char* string = strArray[rank];

    if(!parse_board_files(board, rank, string, strlen(string))) return false;
  }
  return true;
}

bool parse_board_files(Piece* board, int rank, const char string[], int strLength)
{
  for(int index = 0, file = 0; index < strLength; index += 1)
	{
    if(file >= BOARD_FILES) return false;

    if(!parse_board_symbol(board, rank, &file, string[index])) return false;
	}
	return true;
}

bool parse_board_symbol(Piece* board, int rank, int* file, char symbol)
{
	int blanks = (symbol - '0');

	if(NUMBER_IN_BOUNDS(blanks, 0, BOARD_FILES))
	{
		return parse_board_blanks(board, rank, file, blanks);
	}
	Piece piece;
	if(!parse_board_piece(&piece, symbol)) return false;

	Point point = RANK_FILE_POINT(rank, *file);

	board[point] = piece; *file += 1; return true;
}

bool parse_board_blanks(Piece* board, int rank, int* file, int blanks)
{
	int totalFiles = (*file + blanks);

	if(totalFiles > BOARD_FILES) return false;

	for(; *file < totalFiles; *file += 1)
	{
		board[RANK_FILE_POINT(rank, *file)] = PIECE_NONE;
	}
	return true;
}

bool parse_board_piece(Piece* piece, char symbol)
{
  for(Type type = TYPE_PAWN; type <= TYPE_KING; type += 1)
  {
    if(symbol == WHITE_TYPE_SYMBOLS[type])
    {
      piece->type = type; piece->team = TEAM_WHITE; return true;
    }
    else if(symbol == BLACK_TYPE_SYMBOLS[type])
    {
      piece->type = type; piece->team = TEAM_BLACK; return true;
    }
  }
  return false;
}

char chess_piece_symbol(Piece piece)
{
	if(piece.team == TEAM_WHITE) return WHITE_TYPE_SYMBOLS[piece.type];
	if(piece.team == TEAM_BLACK) return BLACK_TYPE_SYMBOLS[piece.type];

	return SYMBOL_NONE;
}
