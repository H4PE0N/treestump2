
#ifndef EXECUTE_CHESS_MOVES_H
#define EXECUTE_CHESS_MOVES_H

bool execute_chess_move(Piece* board, State* state, Move move);

void update_state_values(State* state, const Piece board[], Move move);

bool moved_reset_castle(State* state, const Piece board[], Move move);

bool reset_king_ability(State* state, Piece kingPiece);

bool reset_rook_ability(State* state, Piece rookPiece, Point rookPoint);

Type move_promote_type(Move move);

Team move_promote_team(Move move);

Piece move_promote_piece(Move move);

bool execute_board_move(Piece* board, Move move);

bool execute_passant_move(Piece* board, Move move);

bool execute_promote_move(Piece* board, Move move);

bool execute_castle_move(Piece* board, Move move);

Point castle_rook_point(Move castleMove);

Point castle_middle_point(Move castleMove);

#endif
