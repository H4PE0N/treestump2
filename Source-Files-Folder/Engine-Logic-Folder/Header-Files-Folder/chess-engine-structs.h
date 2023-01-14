
#ifndef CHESS_ENGINE_STRUCTS_H
#define CHESS_ENGINE_STRUCTS_H

typedef enum Type
{
	TYPE_NONE, TYPE_PAWN, TYPE_KNIGHT, TYPE_BISHOP, TYPE_ROOK, TYPE_QUEEN, TYPE_KING
} Type;

typedef enum Team
{
	TEAM_NONE, TEAM_WHITE, TEAM_BLACK
} Team;

typedef struct Piece
{
  Team team;
  Type type;
} Piece;

typedef int Point;

typedef struct State
{
  Team current;
  int castle;
  Point passant;
  int clock;
  int turns;
} State;

#endif
