
#include "../Header-Files-Folder/engine-include-file.h"

// The score of the board is positive for whites favour and negative for blacks favour
int board_state_score(const Piece board[], State state)
{
	if(check_mate_ending(board, state))
	{
		return TEAM_WEIGHT_SCORE(MATE_SCORE, state.current);
	}
	else if(check_draw_ending(board, state))
	{
		return TEAM_WEIGHT_SCORE(DRAW_SCORE, state.current);
	}
	return board_pieces_score(board);
}

int board_pieces_score(const Piece board[])
{
	int piecesScore = 0;
	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		if(!chess_piece_exists(board[point])) continue;

		piecesScore += chess_piece_score(board[point], point);
	}
	return piecesScore;
}

int chess_piece_score(Piece piece, Point point)
{
	int pointRank = POINT_RANK_MACRO(point);

	int rank = TEAM_MATRIX_RANK(pointRank, piece.team);
	int file = POINT_FILE_MACRO(point);

	int typeScore = PIECE_TYPE_SCORES[piece.type];
	int matrixScore = TYPE_SCORE_MATRIX[piece.type][rank][file];

	int pieceScore = (typeScore * TYPE_FACTOR + matrixScore * MATRIX_FACTOR);

	return TEAM_WEIGHT_SCORE(pieceScore, piece.team);
}
