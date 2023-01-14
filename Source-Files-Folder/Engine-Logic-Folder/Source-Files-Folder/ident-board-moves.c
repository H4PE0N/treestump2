
#include "../Header-Files-Folder/englog-include-file.h"

bool castle_move_ident(State state, Move move, Piece piece)
{
	if(!move_inside_board(move) || !chess_piece_exists(piece)) return false;

	if(piece.type != TYPE_KING) return false;

	int movePatt = (move.stop - move.start);

	return ((movePatt == KSIDE_OFFSET) || (movePatt == QSIDE_OFFSET));
}

bool passant_move_ident(State state, Move move, Piece piece)
{
	if(!move_inside_board(move) || !chess_piece_exists(piece)) return false;

	int stopRank = POINT_RANK_MACRO(move.stop);
	int stopFile = POINT_FILE_MACRO(move.stop);

	if(piece.type != TYPE_PAWN) return false;
	if((stopFile + 1) != state.passant) return false;

	if((state.current == TEAM_WHITE) && (stopRank == BLACK_PASSANT_RANK)) return true;
	if((state.current == TEAM_BLACK) && (stopRank == WHITE_PASSANT_RANK)) return true;

	return false;
}

bool promote_move_ident(State state, Move move, Piece piece)
{
	if(!move_inside_board(move) || !chess_piece_exists(piece)) return false;

	int stopRank = POINT_RANK_MACRO(move.stop);

	if(piece.type != TYPE_PAWN) return false;

	if((state.current == TEAM_WHITE) && (stopRank == BLACK_START_RANK)) return true;
	if((state.current == TEAM_BLACK) && (stopRank == WHITE_START_RANK)) return true;

	return false;
}

bool double_move_ident(State state, Move move, Piece piece)
{
	if(!move_inside_board(move) || !chess_piece_exists(piece)) return false;

	int rankOffset = move_rank_offset(move, piece.team);

	return ((piece.type == TYPE_PAWN) && (rankOffset == 2));
}
