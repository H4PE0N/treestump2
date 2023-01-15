
#include "../Header-Files-Folder/englog-include-file.h"

bool move_fully_legal(const Piece board[], State state, Move move)
{
	if(!move_inside_board(move)) return false;

	if(state.current != board[move.start].team) return false;

	if(!move_pseudo_legal(board, state, move)) return false;

	return move_check_handler(board, state, move);
}

bool move_pseudo_legal(const Piece board[], State state, Move move)
{
	if(!move_ability_valid(move, state)) return false;

	return board_move_legal(board, move);
}

bool board_move_legal(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	if(!move_pattern_valid(move, board[move.start])) return false;

	return move_pattern_fits(board, move);
}

bool piece_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], State state, Point piecePoint)
{
	if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	Move* pattMoves; int pattAmount;
	if(!piece_pattern_moves(&pattMoves, &pattAmount, board, piecePoint)) return false;

	*moveArray = create_move_array(32); *moveAmount = 0;

	for(int index = 0; index < pattAmount; index += 1)
	{
		Move currMove = pattMoves[index];

		if(!pattern_move_legal(&currMove, board, state)) continue;

		if(move_flag_promote(currMove.flag))
		{
			append_promote_moves(*moveArray, moveAmount, currMove);
		}
		else (*moveArray)[(*moveAmount)++] = currMove;
	}
	free(pattMoves); return true;
}

bool piece_legal_points(Point** pointArray, int* pointAmount, const Piece board[], State state, Point piecePoint)
{
	if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	Move* pattMoves; int pattAmount;
	if(!piece_pattern_moves(&pattMoves, &pattAmount, board, piecePoint)) return false;

	*pointArray = create_point_array(32); *pointAmount = 0;

	for(int index = 0; index < pattAmount; index += 1)
	{
		Move currMove = pattMoves[index];

		if(!pattern_move_legal(&currMove, board, state)) continue;

		(*pointArray)[(*pointAmount)++] = currMove.stop;
	}
	free(pattMoves); return true;
}

bool pattern_move_legal(Move* pattMove, const Piece board[], State state)
{
	if(move_points_team(board, *pattMove)) return false;

	if(!correct_move_flag(pattMove, board, state)) return false;

	return move_fully_legal(board, state, *pattMove);
}

void append_promote_moves(Move* moveArray, int* moveAmount, Move promoteMove)
{
	promoteMove.flag = MFLAG_KNIGHT;
	moveArray[(*moveAmount)++] = promoteMove;

	promoteMove.flag = MFLAG_BISHOP;
	moveArray[(*moveAmount)++] = promoteMove;

	promoteMove.flag = MFLAG_ROOK;
	moveArray[(*moveAmount)++] = promoteMove;

	promoteMove.flag = MFLAG_QUEEN;
	moveArray[(*moveAmount)++] = promoteMove;
}

// Maybe remove team from the arguments and instead use info team
bool team_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], State state)
{
	*moveArray = create_move_array(256); *moveAmount = 0;

	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		if(!piece_teams_team(board[point].team, state.current)) continue;

		Move* pieceMoves; int addingAmount;
		if(!piece_legal_moves(&pieceMoves, &addingAmount, board, state, point)) continue;

		append_move_array(*moveArray, moveAmount, pieceMoves, addingAmount);

		free(pieceMoves);
	}
	return true;
}
