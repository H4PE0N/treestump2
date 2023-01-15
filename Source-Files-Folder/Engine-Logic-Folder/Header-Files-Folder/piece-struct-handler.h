
#ifndef PIECE_STRUCT_HANDLER_H
#define PIECE_STRUCT_HANDLER_H

Team piece_team_enemy(Team team);

bool chess_piece_exists(Piece piece);

bool piece_type_exists(Type type);

bool piece_team_exists(Team team);

bool piece_teams_team(Team team1, Team team2);

bool board_points_enemy(const Piece board[], Point point1, Point point2);

bool piece_teams_enemy(Team team1, Team team2);

Point board_king_point(const Piece board[], Team team);

bool comp_chess_pieces(Piece piece1, Piece piece2);

Piece* copy_chess_board(const Piece board[]);

#endif
