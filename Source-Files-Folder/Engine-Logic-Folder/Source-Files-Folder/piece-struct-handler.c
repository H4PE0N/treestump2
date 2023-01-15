
#include "../Header-Files-Folder/englog-include-file.h"

Team piece_team_enemy(Team team)
{
  if(team == TEAM_WHITE) return TEAM_BLACK;
  if(team == TEAM_BLACK) return TEAM_WHITE;

  return TEAM_NONE;
}

bool chess_piece_exists(Piece piece)
{
  if(!piece_type_exists(piece.type)) return false;

  return piece_team_exists(piece.team);
}

bool piece_team_exists(Team team)
{
  return (team == TEAM_WHITE || team == TEAM_BLACK);
}

bool piece_type_exists(Type type)
{
  return NUMBER_IN_BOUNDS(type, 1, 6);
}

bool piece_teams_team(Team team1, Team team2)
{
  bool blackBool = ((team1 == TEAM_BLACK) && (team2 == TEAM_BLACK));

  bool whiteBool = ((team1 == TEAM_WHITE) && (team2 == TEAM_WHITE));

  return (blackBool || whiteBool);
}

bool board_points_enemy(const Piece board[], Point point1, Point point2)
{
  return piece_teams_enemy(board[point1].team, board[point2].team);
}

bool piece_teams_enemy(Team team1, Team team2)
{
  bool blackBool = ((team1 == TEAM_BLACK) && (team2 == TEAM_WHITE));

  bool whiteBool = ((team1 == TEAM_WHITE) && (team2 == TEAM_BLACK));

  return (blackBool || whiteBool);
}

bool comp_chess_pieces(Piece piece1, Piece piece2)
{
  bool teamBool = (piece1.team == piece2.team);
  bool typeBool = (piece1.type == piece2.type);

  return (teamBool && typeBool);
}

Piece* copy_chess_board(const Piece board[])
{
	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_POINTS);

	memcpy(boardCopy, board, sizeof(Piece) * BOARD_POINTS);

	return boardCopy;
}
