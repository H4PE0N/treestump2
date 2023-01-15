
#ifndef MOVE_PATTERNS_VALID_H
#define MOVE_PATTERNS_VALID_H

bool pawn_pattern_valid(Move move, Team team);

bool knight_pattern_valid(Move move, Team team);

bool bishop_pattern_valid(Move move, Team team);

bool queen_pattern_valid(Move move, Team team);

bool king_pattern_valid(Move move, Team team);

bool rook_pattern_valid(Move move, Team team);

bool castle_pattern_valid(Move move, Team team);

bool double_pattern_valid(Move move, Team team);

bool passant_pattern_valid(Move move, Team team);

bool promote_pattern_valid(Move move, Team team);

#endif
