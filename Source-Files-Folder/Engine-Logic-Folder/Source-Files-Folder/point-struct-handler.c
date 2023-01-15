
#include "../Header-Files-Folder/englog-include-file.h"

Point board_king_point(const Piece board[], Team team)
{
	Piece kingPiece = {.type = TYPE_KING, .team = team};

	for(int index = 0; index < BOARD_POINTS; index += 1)
	{
		Point point = (team == TEAM_WHITE) ? (BOARD_POINTS - index - 1) : index;

    if(comp_chess_pieces(board[point], kingPiece)) return point;
	}
	return POINT_NONE;
}

int array_point_index(const Point pointArray[], int amount, Point point)
{
	for(int index = 0; index < amount; index += 1)
	{
		if(pointArray[index] == point) return index;
	}
	return INDEX_NONE;
}

bool delete_array_point(Point* pointArray, int amount, int delIndex)
{
	if(!((delIndex >= 0) && (delIndex < amount))) return false;

	for(int index = delIndex; index < (amount - 1); index += 1)
	{
		pointArray[index] = pointArray[index + 1];
	}
	pointArray[amount - 1] = POINT_NONE; return true;
}

Point* create_point_array(int amount)
{
	Point* pointArray = malloc(sizeof(Point) * (amount + 1));

	memset(pointArray, POINT_NONE, sizeof(Point) * (amount + 1));

	return pointArray;
}

int point_array_amount(const Point pointArray[])
{
	int amount = 0;

	while(POINT_INSIDE_BOARD(pointArray[amount])) amount += 1;

	return amount;
}

Point passant_pawn_point(State state)
{
	if(state.passant == 0) return POINT_NONE;

	if(state.current == TEAM_NONE) return POINT_NONE;

	Team enemyTeam = piece_team_enemy(state.current);

	int pawnRank = TEAM_PASSANT_RANK(enemyTeam);

	return RANK_FILE_POINT(pawnRank, (state.passant - 1));
}
