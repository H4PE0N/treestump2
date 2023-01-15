
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

// bool piece_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], Info info, Point piecePoint)
// {
// 	if(!POINT_INSIDE_BOARD(piecePoint)) return false;
//
// 	Move* pattMoves; int pattAmount;
// 	if(!piece_pattern_moves(&pattMoves, &pattAmount, board, piecePoint)) return false;
//
// 	*moveArray = create_move_array(32); *moveAmount = 0;
//
// 	for(int index = 0; index < pattAmount; index += 1)
// 	{
// 		Move currentMove = pattMoves[index];
//
// 		if(!pattern_move_legal(&currentMove, board, info)) continue;
//
// 		if(MOVE_PROMOTE_FLAG(currentMove))
// 			append_promote_moves(*moveArray, moveAmount, currentMove);
//
// 		else (*moveArray)[(*moveAmount)++] = currentMove;
// 	}
// 	free(pattMoves); return true;
// }

// bool piece_legal_points(Point** pointArray, int* pointAmount, const Piece board[], Info info, Point piecePoint)
// {
// 	if(!POINT_INSIDE_BOARD(piecePoint)) return false;
//
// 	Move* pattMoves; int pattAmount;
// 	if(!piece_pattern_moves(&pattMoves, &pattAmount, board, piecePoint)) return false;
//
// 	*pointArray = create_point_array(32); *pointAmount = 0;
//
// 	for(int index = 0; index < pattAmount; index += 1)
// 	{
// 		Move currentMove = pattMoves[index];
//
// 		if(!pattern_move_legal(&currentMove, board, info)) continue;
//
// 		(*pointArray)[(*pointAmount)++] = MOVE_STOP_MACRO(currentMove);
// 	}
// 	free(pattMoves); return true;
// }

// bool pattern_move_legal(Move* patternMove, const Piece board[], Info info)
// {
// 	if(MOVE_POINTS_TEAM(board, *patternMove)) return false;
//
// 	if(!correct_move_flag(patternMove, board, info)) return false;
//
// 	return move_fully_legal(board, info, *patternMove);
// }
//
// void append_promote_moves(Move* moveArray, int* moveAmount, Move promoteMove)
// {
// 	moveArray[(*moveAmount)++] = ALLOC_MOVE_FLAG(promoteMove, MOVE_FLAG_KNIGHT);
//
// 	moveArray[(*moveAmount)++] = ALLOC_MOVE_FLAG(promoteMove, MOVE_FLAG_BISHOP);
//
// 	moveArray[(*moveAmount)++] = ALLOC_MOVE_FLAG(promoteMove, MOVE_FLAG_ROOK);
//
// 	moveArray[(*moveAmount)++] = ALLOC_MOVE_FLAG(promoteMove, MOVE_FLAG_QUEEN);
// }
//
// // Maybe remove team from the arguments and instead use info team
// bool team_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], Info info, uint8_t team)
// {
// 	if(!NORMAL_TEAM_EXISTS(team)) return false;
//
// 	*moveArray = create_move_array(256); *moveAmount = 0;
//
// 	for(Point point = 0; point < BOARD_LENGTH; point += 1)
// 	{
// 		uint8_t currentTeam = BOARD_POINT_TEAM(board, point);
// 		if(!NORMAL_TEAMS_TEAM(currentTeam, team)) continue;
//
// 		Move* pieceMoves; int addingAmount;
// 		if(!piece_legal_moves(&pieceMoves, &addingAmount, board, info, point)) continue;
//
// 		append_move_array(*moveArray, moveAmount, pieceMoves, addingAmount);
//
// 		free(pieceMoves);
// 	}
// 	return true;
// }
