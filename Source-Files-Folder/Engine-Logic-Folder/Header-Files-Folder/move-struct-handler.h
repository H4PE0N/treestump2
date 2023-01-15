
#ifndef MOVE_STRUCT_HANDLER_H
#define MOVE_STRUCT_HANDLER_H

bool move_inside_board(Move move);

bool move_flag_promote(MFlag flag);

Point pawn_passant_point(Move move);

int normal_rank_offset(Move move);

int normal_file_offset(Move move);

int move_file_offset(Move move, Team team);

int move_rank_offset(Move move, Team team);

bool move_points_team(const Piece board[], Move move);

Move start_stop_move(Point startPoint, Point stopPoint);

int move_array_amount(const Move moveArray[]);

void paste_capped_moves(Move* moves1, int amount1, const Move moves2[], int amount2);

void paste_move_array(Move* moves1, const Move moves2[], int moveAmount);

Move* copy_move_array(const Move moveArray[], int moveAmount);

void append_move_array(Move* moves1, int* amount1, const Move moves2[], int amount2);

Move* create_move_array(int amount);

#endif
