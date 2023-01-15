
#include "../Header-Files-Folder/englog-include-file.h"

// This function should check if the inputted move prevents check.
// It can do that by executing the move, and see if the king is in check
bool move_check_handler(const Piece board[], State state, Move move)
{
	if(!move_inside_board(move)) return false;

	if(castle_move_ident(state, move, board[move.start]))
	{
		return castle_prevent_check(board, state, move);
	}
	return move_prevent_check(board, state, move);
}

bool castle_prevent_check(const Piece board[], State state, Move castleMove)
{
	if(king_inside_check(board, castleMove.start)) return false;

	Move middleMove = castle_middle_move(castleMove);

	if(!move_prevent_check(board, state, middleMove)) return false;

	return move_prevent_check(board, state, castleMove);
}

Move castle_middle_move(Move castleMove)
{
	Point middlePoint = castle_middle_point(castleMove);

	return (Move) {.start = castleMove.start, .stop = middlePoint};
}

Point castle_middle_point(Move castleMove)
{
	int kingFile = POINT_FILE_MACRO(castleMove.start);
	int kingRank = POINT_RANK_MACRO(castleMove.start);

	int fileOffset = normal_file_offset(castleMove);
	int fileFactor = MOVE_OFFSET_FACTOR(fileOffset);

	return RANK_FILE_POINT(kingRank, (kingFile + fileFactor));
}

bool move_prevent_check(const Piece board[], State state, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece* boardCopy = copy_chess_board(board);

	bool result = prevent_check_test(boardCopy, state, move);

	free(boardCopy); return result;
}

bool prevent_check_test(Piece* boardCopy, State stateCopy, Move move)
{
	Team startTeam = boardCopy[move.start].team;

	if(!execute_chess_move(boardCopy, &stateCopy, move)) return false;

	Point kingPoint = board_king_point(boardCopy, startTeam);
	if(kingPoint == POINT_NONE) return false;

	return !king_inside_check(boardCopy, kingPoint);
}
