
#include "../Header-Files-Folder/englog-include-file.h"

bool move_inside_board(Move move)
{
	bool startBool = POINT_INSIDE_BOARD(move.start);

	bool stopBool = POINT_INSIDE_BOARD(move.stop);

	return (startBool && stopBool && (move.start != move.stop));
}

bool move_flag_promote(MFlag flag)
{
  return ((flag == MFLAG_QUEEN) || (flag == MFLAG_ROOK) ||
    (flag == MFLAG_KNIGHT) || (flag == MFLAG_BISHOP));
}

Point pawn_passant_point(Move move)
{
  int rank = POINT_RANK_MACRO(move.start);

  int file = POINT_FILE_MACRO(move.stop);

  return RANK_FILE_POINT(rank, file);
}

int normal_rank_offset(Move move)
{
	return (POINT_RANK_MACRO(move.stop) - POINT_RANK_MACRO(move.start));
}

int normal_file_offset(Move move)
{
	return (POINT_FILE_MACRO(move.stop) - POINT_FILE_MACRO(move.start));
}

int move_file_offset(Move move, Team team)
{
  return normal_file_offset(move);
}

int move_rank_offset(Move move, Team team)
{
	int8_t rankOffset = normal_rank_offset(move);

	if(team == TEAM_WHITE) return (rankOffset * WHITE_MOVE_VALUE);

	else return (rankOffset * BLACK_MOVE_VALUE);
}
