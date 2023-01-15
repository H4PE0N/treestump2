
#ifndef GUESS_ORDER_MOVES_H
#define GUESS_ORDER_MOVES_H

bool guess_moves_scores(int** moveScores, const Move moveArray[], int moveAmount, const Piece board[], State state, Team evalTeam);

int guess_move_score(const Piece board[], State state, Team evalTeam, Move move);

bool guess_order_moves(Move* moveArray, int moveAmount, const Piece board[], State state, Team evalTeam);

bool ordered_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], State state, Team evalTeam);

#endif
