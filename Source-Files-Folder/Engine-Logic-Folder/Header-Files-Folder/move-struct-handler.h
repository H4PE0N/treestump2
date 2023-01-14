
#ifndef MOVE_STRUCT_HANDLER_H
#define MOVE_STRUCT_HANDLER_H

bool move_inside_board(Move move);

bool move_flag_promote(MFlag flag);

Point pawn_passant_point(Move move);

int normal_rank_offset(Move move);

int normal_file_offset(Move move);

int move_file_offset(Move move, Team team);

int move_rank_offset(Move move, Team team);

#endif
