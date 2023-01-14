
#include "../Header-Files-Folder/englog-include-file.h"

Team chess_team_enemy(Team team)
{
  if(team == TEAM_WHITE) return TEAM_BLACK;
  if(team == TEAM_BLACK) return TEAM_WHITE;

  return TEAM_NONE;
}

bool chess_piece_exists(Piece piece)
{
  if(!NUMBER_IN_BOUNDS(piece.type, 1, 6)) return false;

  return (piece.team == TEAM_WHITE || piece.team == TEAM_BLACK);
}
