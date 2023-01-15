
#include "../Header-Files-Folder/englog-include-file.h"

bool execute_chess_move(Piece* board, State* state, Move move)
{
	if(!move_inside_board(move)) return false;

	update_state_values(state, board, move);

	if(move_flag_promote(move.flag))
		return execute_promote_move(board, move);

	if(move.flag == MFLAG_CASTLE)
		return execute_castle_move(board, move);

	if(move.flag == MFLAG_PASSANT)
		return execute_passant_move(board, move);

	return execute_board_move(board, move);
}

void update_state_values(State* state, const Piece board[], Move move)
{
	if(state->current == TEAM_BLACK) state->turns += 1;

	state->current = piece_team_enemy(state->current);

	bool stopExists = chess_piece_exists(board[move.stop]);

	if(board[move.start].type == TYPE_PAWN || stopExists) state->clock = 0;

	else state->clock += 1;

	if(move.flag != MFLAG_DOUBLE) state->passant = 0;

	else state->passant = (POINT_FILE_MACRO(move.start) + 1);

	moved_reset_castle(state, board, move);
}

bool moved_reset_castle(State* state, const Piece board[], Move move)
{
	if(board[move.start].type == TYPE_KING)
		return reset_king_ability(state, board[move.start]);

	if(board[move.stop].type == TYPE_ROOK)
		return reset_rook_ability(state, board[move.stop], move.stop);

	if(board[move.start].type == TYPE_ROOK)
		return reset_rook_ability(state, board[move.start], move.start);

	return false;
}

bool reset_king_ability(State* state, Piece kingPiece)
{
	if(kingPiece.type != TYPE_KING) return false;

	if(kingPiece.team == TEAM_WHITE)
		state->castles = CLEAR_WHITE_CASTLE(state->castles);

	else if(kingPiece.team == TEAM_BLACK)
		state->castles = CLEAR_BLACK_CASTLE(state->castles);

	else return false;

	return true;
}

bool reset_rook_ability(State* state, Piece rookPiece, Point rookPoint)
{
	if(rookPiece.type != TYPE_ROOK) return false;

	if(rookPoint == WROOK_QSIDE_POINT)
		state->castles = CLEAR_WHITE_QSIDE(state->castles);

	else if(rookPoint == WROOK_KSIDE_POINT)
		state->castles = CLEAR_WHITE_KSIDE(state->castles);

	else if(rookPoint == BROOK_QSIDE_POINT)
		state->castles = CLEAR_BLACK_QSIDE(state->castles);

	else if(rookPoint == BROOK_KSIDE_POINT)
		state->castles = CLEAR_BLACK_KSIDE(state->castles);

	else return false;

	return true;
}

Type move_promote_type(Move move)
{
	if(move.flag == MFLAG_QUEEN) return TYPE_QUEEN;

	if(move.flag == MFLAG_ROOK) return TYPE_ROOK;

	if(move.flag == MFLAG_BISHOP) return TYPE_BISHOP;

	if(move.flag == MFLAG_KNIGHT) return TYPE_KNIGHT;

	return TYPE_NONE;
}

Team move_promote_team(Move move)
{
	int stopRank = POINT_RANK_MACRO(move.stop);

	if(stopRank == WHITE_START_RANK) return TEAM_BLACK;

	if(stopRank == BLACK_START_RANK) return TEAM_WHITE;

	return TEAM_NONE;
}

Piece move_promote_piece(Move move)
{
	Team team = move_promote_team(move);

	Type type = move_promote_type(move);

	if((team == TEAM_NONE) || (type == TYPE_NONE)) return PIECE_NONE;

	return (Piece) {.team = team, .type = type};
}

bool execute_board_move(Piece* board, Move move)
{
	board[move.stop] = board[move.start];
	board[move.start] = PIECE_NONE;

	return true;
}

bool execute_passant_move(Piece* board, Move move)
{
	Point pawnPoint = pawn_passant_point(move);

	board[move.stop] = board[move.start];
	board[move.start] = PIECE_NONE;
	board[pawnPoint] = PIECE_NONE;

	return true;
}

bool execute_promote_move(Piece* board, Move move)
{
	Piece promotePiece = move_promote_piece(move);
	if(!chess_piece_exists(promotePiece)) return false;

	board[move.stop] = promotePiece;
	board[move.start] = PIECE_NONE;

	return true;
}

bool execute_castle_move(Piece* board, Move move)
{
	Point startRook = castle_rook_point(move);
	Point stopRook = castle_middle_point(move);

	if((startRook == POINT_NONE) || (stopRook == POINT_NONE)) return false;

	board[move.stop] = board[move.start];
	board[move.start] = PIECE_NONE;

	board[stopRook] = board[startRook];
	board[startRook] = PIECE_NONE;

	return true;
}
