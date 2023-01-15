
#include "../Header-Files-Folder/englog-include-file.h"

bool move_ability_valid(Move move, State state)
{
	if(move.flag == MFLAG_CASTLE)
		return castle_ability_valid(move, state);

	if(move.flag == MFLAG_PASSANT)
		return passant_ability_valid(move, state);

	return true;
}

bool castle_ability_valid(Move move, State state)
{
	if(!move_inside_board(move)) return false;

	int movePatt = (move.stop - move.start);

	if((move.start == WHITE_KING_POINT) && (movePatt == KSIDE_OFFSET))
		return (MASK_WHITE_KSIDE(state.castle) == WHITE_KSIDE);

	if((move.start == WHITE_KING_POINT) && (movePatt == QSIDE_OFFSET))
		return (MASK_WHITE_QSIDE(state.castle) == WHITE_QSIDE);

	if((move.start == BLACK_KING_POINT) && (movePatt == KSIDE_OFFSET))
		return (MASK_BLACK_KSIDE(state.castle) == BLACK_KSIDE);

	if((move.start == BLACK_KING_POINT) && (movePatt == QSIDE_OFFSET))
		return (MASK_BLACK_QSIDE(state.castle) == BLACK_QSIDE);

	return false;
}

bool passant_ability_valid(Move move, State state)
{
	if(!move_inside_board(move)) return false;

	int stopFile = POINT_FILE_MACRO(move.stop);

	return ((stopFile + 1) == state.passant);
}
