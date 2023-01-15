
#include "../Header-Files-Folder/englog-include-file.h"

bool king_inside_check(const Piece board[], Point kingPoint)
{
	if(!POINT_INSIDE_BOARD(kingPoint)) return false;

	Team kingTeam = board[kingPoint].team;

	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		Team currTeam = board[point].team;
		if(!piece_teams_enemy(currTeam, kingTeam)) continue;

		if(piece_does_check(board, kingPoint, point)) return true;
	}
	return false;
}

bool piece_does_check(const Piece board[], Point kingPoint, Point point)
{
	if(!POINTS_INSIDE_BOARD(point, kingPoint)) return false;

	if(!board_points_enemy(board, kingPoint, point)) return false;

	Move move = {.start = point, .stop = kingPoint};

	return board_move_legal(board, move);
}

bool game_still_running(const Piece board[], State state)
{
	if(check_mate_ending(board, state)) return false;

	if(check_draw_ending(board, state)) return false;

	return true;
}

bool check_mate_ending(const Piece board[], State state)
{
	Point kingPoint = board_king_point(board, state.current);
	if(kingPoint == POINT_NONE) return false;

	if(!king_inside_check(board, kingPoint)) return false;

	if(team_pieces_movable(board, state, state.current)) return false;

	return true;
}

bool check_draw_ending(const Piece board[], State state)
{
	if(!piece_team_exists(state.current)) return false;

	if(state.clock >= 100) return true;

	if(little_material_draw(board)) return true;

	Point kingPoint = board_king_point(board, state.current);
	if(kingPoint == POINT_NONE) return false;

	if(king_inside_check(board, kingPoint)) return false;

	if(team_pieces_movable(board, state, state.current)) return false;

	return true;
}
/*
if(knightAmount >= 2) return false;

if((knightAmount >= 1) && (blackBishops || whiteBishops)) return false;

if(blackBishops && whiteBishops) return false;

return true;
*/
bool little_material_draw(const Piece board[])
{
	int blackBishops = 0, whiteBishops = 0, knightAmount = 0;

	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		if(!chess_piece_exists(board[point])) continue;

		Type type = board[point].type;

		if((type == TYPE_ROOK) || (type == TYPE_PAWN) || (type == TYPE_QUEEN)) return false;

		if((type != TYPE_KNIGHT) && (type != TYPE_BISHOP)) continue;


		if(type == TYPE_KNIGHT) knightAmount += 1;

		else if(POINT_SQAURE_WHITE(point)) whiteBishops += 1;

		else blackBishops += 1;


		if(knightAmount >= 2) return false;

		if((knightAmount >= 1) && (blackBishops || whiteBishops)) return false;

		if(blackBishops && whiteBishops) return false;
	}
	return true;
}

bool team_pieces_movable(const Piece board[], State state, Team team)
{
	if(!piece_team_exists(team)) return false;

	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		if(!piece_teams_team(board[point].team, team)) continue;

		if(chess_piece_movable(board, state, point)) return true;
	}
	return false;
}

bool chess_piece_movable(const Piece board[], State state, Point piecePoint)
{
	if(!POINT_INSIDE_BOARD(piecePoint)) return false;

	Move* moveArray; int moveAmount;
	if(!piece_pattern_moves(&moveArray, &moveAmount, board, piecePoint)) return false;

	bool result = piece_movable_test(board, state, moveArray, moveAmount);

	free(moveArray); return result;
}

bool piece_movable_test(const Piece board[], State state, const Move moveArray[], int moveAmount)
{
	for(int index = 0; index < moveAmount; index += 1)
	{
		Move move = moveArray[index];

		if(!correct_move_flag(&move, board, state)) continue;

		if(move_fully_legal(board, state, move)) return true;
	}
	return false;
}

bool move_deliver_check(const Piece board[], State state, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece* boardCopy = copy_chess_board(board);

	bool result = deliver_check_test(boardCopy, state, move);

	free(boardCopy); return result;
}

bool deliver_check_test(Piece* boardCopy, State stateCopy, Move move)
{
	if(!execute_chess_move(boardCopy, &stateCopy, move)) return false;

	Point kingPoint = board_king_point(boardCopy, stateCopy.current);
	if(kingPoint == POINT_NONE) return false;

	return king_inside_check(boardCopy, kingPoint);
}

bool move_deliver_mate(const Piece board[], State state, Move move)
{
	if(!move_inside_board(move)) return false;

	Piece* boardCopy = copy_chess_board(board);

	bool result = deliver_mate_test(boardCopy, state, move);

	free(boardCopy); return result;
}

bool deliver_mate_test(Piece* boardCopy, State stateCopy, Move move)
{
	if(!execute_chess_move(boardCopy, &stateCopy, move)) return false;

	return check_mate_ending(boardCopy, stateCopy);
}
