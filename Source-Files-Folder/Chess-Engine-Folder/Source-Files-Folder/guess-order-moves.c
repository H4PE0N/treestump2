
#include "../Header-Files-Folder/engine-include-file.h"

bool ordered_legal_moves(Move** moveArray, int* moveAmount, const Piece board[], State state, Team evalTeam)
{
	if(!team_legal_moves(moveArray, moveAmount, board, state)) return false;

	return guess_order_moves(*moveArray, *moveAmount, board, state, evalTeam);
}

bool guess_order_moves(Move* moveArray, int moveAmount, const Piece board[], State state, Team evalTeam)
{
	if(moveAmount <= 0) return false;

	int* moveScores;
	if(!guess_moves_scores(&moveScores, moveArray, moveAmount, board, state, evalTeam)) return false;

	qsort_moves_scores(moveArray, moveScores, moveAmount, evalTeam);

	free(moveScores); return true;
}

bool guess_moves_scores(int** moveScores, const Move moveArray[], int moveAmount, const Piece board[], State state, Team evalTeam)
{
	if(moveAmount <= 0) return false;

	*moveScores = malloc(sizeof(int) * moveAmount);
	memset(*moveScores, 0, sizeof(int) * moveAmount);

	for(int index = 0; index < moveAmount; index += 1)
	{
		(*moveScores)[index] = guess_move_score(board, state, evalTeam, moveArray[index]);
	}
	return true;
}

// Make this guess function better, it will benifit
int guess_move_score(const Piece board[], State state, Team evalTeam, Move move)
{
	int moveScore = 0; Type stopType = board[move.stop].type;

	if(stopType != TYPE_NONE)
	{
		Type startType = board[move.start].type;

		int stopScore = PIECE_TYPE_SCORES[stopType];
		int startScore = PIECE_TYPE_SCORES[startType];

		moveScore = (10 * stopScore - startScore);
	}
	if(move_flag_promote(move.flag)) moveScore += move_promote_type(move);

	return TEAM_WEIGHT_SCORE(moveScore, evalTeam);
}
