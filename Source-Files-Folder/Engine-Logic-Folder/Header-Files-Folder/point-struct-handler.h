
#ifndef POINT_STRUCT_HANDLER_H
#define POINT_STRUCT_HANDLER_H

Point board_king_point(const Piece board[], Team team);

bool board_points_team(const Piece board[], Point point1, Point point2);

bool board_points_enemy(const Piece board[], Point point1, Point point2);

int array_point_index(const Point pointArray[], int amount, Point point);

bool delete_array_point(Point* pointArray, int amount, int delIndex);

int point_array_amount(const Point pointArray[]);

Point* create_point_array(int amount);

Point passant_pawn_point(State state);

#endif
