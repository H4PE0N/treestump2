
#include "../Header-Files-Folder/englog-include-file.h"

bool piece_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(board[piecePoint].type == TYPE_PAWN)
    return pawn_pattern_moves(moves, moveAmount, board, piecePoint);

	if(board[piecePoint].type == TYPE_KNIGHT)
    return knight_pattern_moves(moves, moveAmount, board, piecePoint);

	if(board[piecePoint].type == TYPE_BISHOP)
    return bishop_pattern_moves(moves, moveAmount, board, piecePoint);

	if(board[piecePoint].type == TYPE_ROOK)
    return rook_pattern_moves(moves, moveAmount, board, piecePoint);

	if(board[piecePoint].type == TYPE_QUEEN)
    return queen_pattern_moves(moves, moveAmount, board, piecePoint);

	if(board[piecePoint].type == TYPE_KING)
    return king_pattern_moves(moves, moveAmount, board, piecePoint);

	return false;
}

bool pawn_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	*moves = create_move_array(4); *moveAmount = 0;

  int pieceRank = POINT_RANK_MACRO(piecePoint);
  int pieceFile = POINT_FILE_MACRO(piecePoint);

  Team team = board[piecePoint].team;

	for(uint8_t rank = 0; rank < 2; rank += 1)
	{
		for(uint8_t file = 0; file < 3; file += 1)
		{
			if(rank == 1 && (file == 0 || file == 2) ) continue;

      // This here should be a seperate function:
      int realRank = pieceRank + (rank + 1) * ((team == TEAM_WHITE) ? WHITE_MOVE_VALUE : BLACK_MOVE_VALUE);
			int realFile = (pieceFile - 1) + file;

      if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

			Point point = RANK_FILE_POINT(realRank, realFile);

			(*moves)[(*moveAmount)++] = start_stop_move(piecePoint, point);
		}
	}
	return true;
}

bool knight_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(8); *moveAmount = 0;

  int pieceRank = POINT_RANK_MACRO(piecePoint);
  int pieceFile = POINT_FILE_MACRO(piecePoint);

	for(int rank = 0; rank < 5; rank += 1)
	{
		for(int file = 0; file < 5; file += 1)
		{
			if(rank == file || (rank + file) == 4) continue;
			if(rank == 2 || file == 2) continue;

			int realRank = (pieceRank - 2) + rank;
			int realFile = (pieceFile - 2) + file;

			if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

			Point point = RANK_FILE_POINT(realRank, realFile);

      (*moves)[(*moveAmount)++] = start_stop_move(piecePoint, point);
		}
	}
  return true;
}

bool straight_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(14); *moveAmount = 0;

  int pieceRank = POINT_RANK_MACRO(piecePoint);
  int pieceFile = POINT_FILE_MACRO(piecePoint);

  for(int rank = 0; rank < BOARD_RANKS; rank += 1)
	{
    Point point = RANK_FILE_POINT(rank, pieceFile);
    if(piecePoint == point) continue;

		(*moves)[(*moveAmount)++] = start_stop_move(piecePoint, point);
	}

	for(int file = 0; file < BOARD_FILES; file += 1)
	{
		Point point = RANK_FILE_POINT(pieceRank, file);
    if(piecePoint == point) continue;

		(*moves)[(*moveAmount)++] = start_stop_move(piecePoint, point);
	}
  return true;
}

bool diagonal_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(14); *moveAmount = 0;

  int pieceRank = POINT_RANK_MACRO(piecePoint);
  int pieceFile = POINT_FILE_MACRO(piecePoint);

  for(int index = -8; index <= 16; index += 1)
	{
		int realRank = (pieceRank + index);
		int realFile = (pieceFile + index);

    if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

		Point point = RANK_FILE_POINT(realRank, realFile);
    if(piecePoint == point) continue;

    (*moves)[(*moveAmount)++] = start_stop_move(piecePoint, point);
	}

	for(int index = -8; index <= 16; index += 1)
	{
		int realRank = (pieceRank + index);
		int realFile = (pieceFile - index);

    if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

		Point point = RANK_FILE_POINT(realRank, realFile);
    if(piecePoint == point) continue;

    (*moves)[(*moveAmount)++] = start_stop_move(piecePoint, point);
	}
  return true;
}

bool rook_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(14); *moveAmount = 0;

  Move* straightMoves; int addingAmount;
  if(straight_pattern_moves(&straightMoves, &addingAmount, board, piecePoint))
  {
    append_move_array(*moves, moveAmount, straightMoves, addingAmount);

    free(straightMoves);
  }
  return true;
}

bool bishop_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(14); *moveAmount = 0;

  Move* diagonalMoves; int addingAmount;
  if(diagonal_pattern_moves(&diagonalMoves, &addingAmount, board, piecePoint))
  {
  	append_move_array(*moves, moveAmount, diagonalMoves, addingAmount);

    free(diagonalMoves);
  }
  return true;
}

bool queen_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(28); *moveAmount = 0;

  Move* diagonalMoves; int addingAmount;
  if(diagonal_pattern_moves(&diagonalMoves, &addingAmount, board, piecePoint))
  {
  	append_move_array(*moves, moveAmount, diagonalMoves, addingAmount);

    free(diagonalMoves);
  }

  Move* straightMoves;
  if(straight_pattern_moves(&straightMoves, &addingAmount, board, piecePoint))
  {
    append_move_array(*moves, moveAmount, straightMoves, addingAmount);

    free(straightMoves);
  }
  return true;
}

bool king_pattern_moves(Move** moves, int* moveAmount, const Piece board[], Point piecePoint)
{
  if(!POINT_INSIDE_BOARD(piecePoint)) return false;

  *moves = create_move_array(10); *moveAmount = 0;

  int pieceRank = POINT_RANK_MACRO(piecePoint);
  int pieceFile = POINT_FILE_MACRO(piecePoint);

  for(int rank = 0; rank < 3; rank += 1)
	{
		for(int file = 0; file < 5; file += 1)
		{
      if((file == 0 || file == 4) && rank != 1) continue;

			int realRank = (pieceRank - 1) + rank;
			int realFile = (pieceFile - 2) + file;

      if(!RANK_FILE_INSIDE(realRank, realFile)) continue;

      Point point = RANK_FILE_POINT(realRank, realFile);
      if(piecePoint == point) continue;

			(*moves)[(*moveAmount)++] = start_stop_move(piecePoint, point);
		}
	}
	return true;
}
