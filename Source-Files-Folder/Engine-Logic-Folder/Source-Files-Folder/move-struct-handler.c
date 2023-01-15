
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
	int rankOffset = normal_rank_offset(move);

	if(team == TEAM_WHITE) return (rankOffset * WHITE_MOVE_VALUE);

	else return (rankOffset * BLACK_MOVE_VALUE);
}

bool move_points_team(const Piece board[], Move move)
{
  Team startTeam = board[move.start].team;
  Team stopTeam = board[move.stop].team;

  return piece_teams_team(startTeam, stopTeam);
}

Move start_stop_move(Point startPoint, Point stopPoint)
{
	return (Move) {.start = startPoint, .stop = stopPoint};
}

int move_array_amount(const Move moveArray[])
{
	int moveAmount = 0;

	while(move_inside_board(moveArray[moveAmount])) moveAmount += 1;

	return moveAmount;
}

void paste_capped_moves(Move* moves1, int amount1, const Move moves2[], int amount2)
{
	int pasteAmount = MIN_NUMBER_VALUE(amount1, amount2);

	paste_move_array(moves1, moves2, pasteAmount);
}

void paste_move_array(Move* moves1, const Move moves2[], int moveAmount)
{
	for(int index = 0; index < moveAmount; index += 1)
	{
		moves1[index] = moves2[index];
	}
}

Move* copy_move_array(const Move moveArray[], int moveAmount)
{
	Move* movesCopy = malloc(sizeof(Move) * moveAmount);

	memcpy(movesCopy, moveArray, sizeof(Move) * moveAmount);

	return movesCopy;
}

void append_move_array(Move* moves1, int* amount1, const Move moves2[], int amount2)
{
	for(int index = 0; index < amount2; index += 1)
	{
		moves1[(*amount1)++] = moves2[index];
	}
}

Move* create_move_array(int amount)
{
	Move* moveArray = malloc(sizeof(Move) * (amount + 1));

	memset(moveArray, 0, sizeof(Move) * (amount + 1));

	return moveArray;
}
