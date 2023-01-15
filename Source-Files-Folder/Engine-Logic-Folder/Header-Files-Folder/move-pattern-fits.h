
#ifndef MOVE_PATTERN_FITS_H
#define MOVE_PATTERN_FITS_H

bool move_pattern_fits(const Piece board[], Move move);

bool normal_pattern_fits(const Piece board[], Move move);

bool clear_moving_path(const Piece board[], Move move);

bool moving_path_values(int* rankFactor, int* fileFactor, int* moveSteps, Move move);

bool passant_pattern_fits(const Piece board[], Move move);

bool castle_pattern_fits(const Piece board[], Move castleMove);

bool pawn_pattern_fits(const Piece board[], Move move);

Point castle_rook_point(Move castleMove);

#endif
