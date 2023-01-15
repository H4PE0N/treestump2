
#include "../Header-Files-Folder/englog-include-file.h"

// This function is going to check if the move-pattern
// fits inside the board (pawn-takes, castling, pawn double jump)
// - the stop piece can't be of same team
// - the stop piece must be empty if the pawn moves forward
// - it must be a rook in the corner, if it is castle
// - the move path is clear (except for the knight)
bool move_pattern_fits(const Piece board[], Move move)
{
	if(move.flag == MFLAG_CASTLE)
		return castle_pattern_fits(board, move);

	if(move.flag == MFLAG_PASSANT)
		return passant_pattern_fits(board, move);

	if(board[move.start].type == TYPE_PAWN)
		return pawn_pattern_fits(board, move);

	return normal_pattern_fits(board, move);
}

bool normal_pattern_fits(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	if(move_points_team(board, move)) return false;

	return clear_moving_path(board, move);
}

bool passant_pattern_fits(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	Point passantPoint = pawn_passant_point(move);

	if(board[move.start].type != TYPE_PAWN) return false;
	if(board[passantPoint].type != TYPE_PAWN) return false;

	if(!board_points_enemy(board, move.start, passantPoint)) return false;

	return !chess_piece_exists(board[move.stop]);
}

// - King is moving
// - Rook in the corner
// - Clear moving path
bool castle_pattern_fits(const Piece board[], Move castleMove)
{
	if(!move_inside_board(castleMove)) return false;

	Team startTeam = board[castleMove.start].team;

	if(board[castleMove.start].type != TYPE_KING) return false;

	Point rookPoint = castle_rook_point(castleMove);
	if(rookPoint == POINT_NONE) return false;

	Team rookTeam = board[rookPoint].team;
	Type rookType = board[rookPoint].type;

	if(!((rookType == TYPE_ROOK) && (rookTeam == startTeam))) return false;

	Move kingRookMove = (Move) {.start = castleMove.start, .stop = rookPoint};

	return clear_moving_path(board, kingRookMove);
}

Point castle_rook_point(Move castleMove)
{
	int movePatt = (castleMove.stop - castleMove.start);

	if((castleMove.start == WHITE_KING_POINT) && (movePatt == KSIDE_OFFSET))
		return WROOK_KSIDE_POINT;

	if((castleMove.start == WHITE_KING_POINT) && (movePatt == QSIDE_OFFSET))
		return WROOK_QSIDE_POINT;

	if((castleMove.start == BLACK_KING_POINT) && (movePatt == KSIDE_OFFSET))
		return BROOK_KSIDE_POINT;

	if((castleMove.start == BLACK_KING_POINT) && (movePatt == QSIDE_OFFSET))
		return BROOK_QSIDE_POINT;

	return POINT_NONE;
}

bool pawn_pattern_fits(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	if(board[move.start].type != TYPE_PAWN) return false;

	Team startTeam = board[move.start].team;
	Team stopTeam = board[move.stop].team;

	int fileOffset = abs(move_file_offset(move, startTeam));
	int rankOffset = move_rank_offset(move, startTeam);

	if((fileOffset == 0) && ((rankOffset == 1) || (rankOffset == 2)))
	{
		if(chess_piece_exists(board[move.stop])) return false;
	}
	else if((fileOffset == 1) && (rankOffset == 1))
	{
		if(!piece_teams_enemy(startTeam, stopTeam)) return false;
	}
	return clear_moving_path(board, move);
}

bool clear_moving_path(const Piece board[], Move move)
{
	if(!move_inside_board(move)) return false;

	if(board[move.start].type == TYPE_KNIGHT) return true;

	int rankFactor, fileFactor, moveSteps;
	if(!moving_path_values(&rankFactor, &fileFactor, &moveSteps, move)) return false;

	int startRank = POINT_RANK_MACRO(move.start);
	int startFile = POINT_FILE_MACRO(move.start);

	for(int index = 0; index <= moveSteps; index += 1)
	{
		int currFile = (startFile + index * fileFactor);
		int currRank = (startRank + index * rankFactor);

		Point point = RANK_FILE_POINT(currRank, currFile);

		if((point == move.start) || (point == move.stop)) continue;

		if(chess_piece_exists(board[point])) return false;
	}
	return true;
}

bool moving_path_values(int* rankFactor, int* fileFactor, int* moveSteps, Move move)
{
	int rankOffset = normal_rank_offset(move);
	int fileOffset = normal_file_offset(move);

	int absRankOffset = abs(rankOffset);
	int absFileOffset = abs(fileOffset);

	bool moveStraight = ((absRankOffset == 0) || (absFileOffset == 0));
	bool moveDiagonal = (absRankOffset == absFileOffset);

	if(!(moveStraight || moveDiagonal)) return false;

	*fileFactor = MOVE_OFFSET_FACTOR(fileOffset);
	*rankFactor = MOVE_OFFSET_FACTOR(rankOffset);

	*moveSteps = MAX_NUMBER_VALUE(absRankOffset, absFileOffset);

	return true;
}
