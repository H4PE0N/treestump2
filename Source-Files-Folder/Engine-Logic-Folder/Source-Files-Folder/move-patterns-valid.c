
#include "../Header-Files-Folder/englog-include-file.h"

bool pawn_pattern_valid(Move move, Team team)
{
	int fileOffset = abs(move_file_offset(move, team));
	int rankOffset = move_rank_offset(move, team);

	if((fileOffset == 1) && (rankOffset == 1)) return true;
	if((fileOffset == 0) && (rankOffset == 1)) return true;

	return false;
}

bool knight_pattern_valid(Move move, Team team)
{
	int fileOffset = abs(move_file_offset(move, team));
	int rankOffset = abs(move_rank_offset(move, team));

	if((fileOffset == 1) && (rankOffset == 2)) return true;
	if((fileOffset == 2) && (rankOffset == 1)) return true;

	return false;
}

bool bishop_pattern_valid(Move move, Team team)
{
	int fileOffset = abs(move_file_offset(move, team));
	int rankOffset = abs(move_rank_offset(move, team));

	return ((fileOffset == rankOffset) && (fileOffset != 0));
}

bool rook_pattern_valid(Move move, Team team)
{
	int fileOffset = abs(move_file_offset(move, team));
	int rankOffset = abs(move_rank_offset(move, team));

	return ((fileOffset == 0) != (rankOffset == 0));
	// != (not equals) is boolean XOR
}

bool queen_pattern_valid(Move move, Team team)
{
	int fileOffset = abs(move_file_offset(move, team));
	int rankOffset = abs(move_rank_offset(move, team));

	if((fileOffset == rankOffset) && (fileOffset != 0)) return true;
	if((fileOffset == 0) != (rankOffset == 0)) return true;

	return false;
}

bool king_pattern_valid(Move move, Team team)
{
	int fileOffset = abs(move_file_offset(move, team));
	int rankOffset = abs(move_rank_offset(move, team));

	return (((fileOffset <= 1) && (rankOffset <= 1)) && (fileOffset || rankOffset));
}

bool castle_pattern_valid(Move move, Team team)
{
	if(!piece_team_exists(team)) return false;

	int movePatt = (move.stop - move.start);

	if((team == TEAM_WHITE) && (move.start != WHITE_KING_POINT)) return false;
	if((team == TEAM_BLACK) && (move.start != BLACK_KING_POINT)) return false;

	return ((movePatt == KSIDE_OFFSET) || (movePatt == QSIDE_OFFSET));
}

bool double_pattern_valid(Move move, Team team)
{
	if(!piece_team_exists(team)) return false;

	int fileOffset = move_file_offset(move, team);
	int rankOffset = move_rank_offset(move, team);

	if(!((fileOffset == 0) && (rankOffset == 2))) return false;

	int startRank = POINT_RANK_MACRO(move.start);

	if((team == TEAM_WHITE) && (startRank == WHITE_PAWN_RANK)) return true;
	if((team == TEAM_BLACK) && (startRank == BLACK_PAWN_RANK)) return true;

	return false;
}

bool passant_pattern_valid(Move move, Team team)
{
	if(!piece_team_exists(team)) return false;

	int stopRank = POINT_RANK_MACRO(move.stop);

	if((team == TEAM_WHITE) && (stopRank != BLACK_PASSANT_RANK)) return false;
	if((team == TEAM_BLACK) && (stopRank != WHITE_PASSANT_RANK)) return false;

	int fileOffset = abs(move_file_offset(move, team));
	int rankOffset = move_rank_offset(move, team);

	return ((fileOffset == 1) && (rankOffset == 1));
}

bool promote_pattern_valid(Move move, Team team)
{
	if(!piece_team_exists(team)) return false;

	int stopRank = POINT_RANK_MACRO(move.stop);

	if((team == TEAM_WHITE) && (stopRank != BLACK_START_RANK)) return false;
	if((team == TEAM_BLACK) && (stopRank != WHITE_START_RANK)) return false;

	return pawn_pattern_valid(move, team);
}
