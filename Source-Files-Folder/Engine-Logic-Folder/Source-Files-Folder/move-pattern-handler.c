
#include "../Header-Files-Folder/englog-include-file.h"

bool move_pattern_valid(Move move, Piece piece)
{
	if(piece.type == TYPE_PAWN)
		return pawn_pattern_handler(move, piece.team);

	if(piece.type == TYPE_KNIGHT)
		return knight_pattern_handler(move, piece.team);

	if(piece.type == TYPE_BISHOP)
		return bishop_pattern_handler(move, piece.team);

	if(piece.type == TYPE_ROOK)
		return rook_pattern_handler(move, piece.team);

	if(piece.type == TYPE_QUEEN)
		return queen_pattern_handler(move, piece.team);

	if(piece.type == TYPE_KING)
		return king_pattern_handler(move, piece.team);

	return false;
}

bool pawn_pattern_handler(Move move, Team team)
{
	if(move.flag == MFLAG_DOUBLE)
		return double_pattern_valid(move, team);

	if(move.flag == MFLAG_PASSANT)
		return passant_pattern_valid(move, team);

	if(move_flag_promote(move.flag))
		return promote_pattern_valid(move, team);

	if(move.flag == MFLAG_NONE)
		return pawn_pattern_valid(move, team);

	return false;
}

bool knight_pattern_handler(Move move, Team team)
{
	if(move.flag != MFLAG_NONE) return false;

	return knight_pattern_valid(move, team);
}

bool bishop_pattern_handler(Move move, Team team)
{
	if(move.flag != MFLAG_NONE) return false;

	return bishop_pattern_valid(move, team);
}

bool rook_pattern_handler(Move move, Team team)
{
	if(move.flag != MFLAG_NONE) return false;

	return rook_pattern_valid(move, team);
}

bool queen_pattern_handler(Move move, Team team)
{
	if(move.flag != MFLAG_NONE) return false;

	return queen_pattern_valid(move, team);
}

bool king_pattern_handler(Move move, Team team)
{
	if(move.flag == MFLAG_CASTLE)
		return castle_pattern_valid(move, team);

	if(move.flag == MFLAG_NONE)
		return king_pattern_valid(move, team);

	return false;
}
