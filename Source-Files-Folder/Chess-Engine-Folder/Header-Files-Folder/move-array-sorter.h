
#ifndef MOVE_ARRAY_SORTER_H
#define MOVE_ARRAY_SORTER_H

void qsort_moves_scores(Move* moveArray, int* moveScores, int amount, Team team);

void qsort_moves_indexis(Move* moveArray, int* moveScores, int index1, int index2, Team team);

int partly_qsort_moves(Move* moveArray, int* moveScores, int index1, int index2, Team team);

void qswap_moves_scores(Move* moveArray, int* moveScores, int index1, int index2);

void qswap_move_scores(int* moveScores, int index1, int index2);

void qswap_array_moves(Move* moveArray, int index1, int index2);

#endif
