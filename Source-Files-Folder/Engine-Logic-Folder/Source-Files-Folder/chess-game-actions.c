
#include "../Header-Files-Folder/englog-include-file.h"

bool move_chess_piece(Piece* board, State* state, Move move)
{
	if(!move_inside_board(move)) return false;

	if(!correct_move_flag(&move, board, *state)) return false;

	if(!move_fully_legal(board, *state, move)) return false;

	return execute_chess_move(board, state, move);

	return false;
}

bool correct_move_flag(Move* move, const Piece board[], State state)
{
	if(!move_inside_board(*move)) return false;

	Piece piece = board[move->start];

	if(piece.type == TYPE_PAWN)
		move->flag = extract_pawn_flag(*move, piece, state);

	else if(piece.type == TYPE_KING)
		move->flag = extract_king_flag(*move, piece, state);

	else move->flag = MFLAG_NONE;

	return true;
}

MFlag extract_pawn_flag(Move move, Piece piece, State state)
{
	if(double_move_ident(state, move, piece)) return MFLAG_DOUBLE;

	if(passant_move_ident(state, move, piece)) return MFLAG_PASSANT;

	if(promote_move_ident(state, move, piece))
		return (move_flag_promote(move.flag) ? move.flag : MFLAG_QUEEN);

	return MFLAG_NONE;
}

MFlag extract_king_flag(Move move, Piece piece, State state)
{
	if(castle_move_ident(state, move, piece)) return MFLAG_CASTLE;

	return MFLAG_NONE;
}
