
#ifndef STRING_BOARD_PARSER_H
#define STRING_BOARD_PARSER_H

bool parse_create_board(Piece** board, State* state, const char fenString[], int strLength);

bool parse_fen_string(Piece* board, State* state, const char fenString[], int strLength);

bool parse_string_array(Piece* board, State* state, char* strArray[]);

bool parse_string_state(State* state, char* strArray[]);

bool parse_string_current(State* state, const char strToken[], int strLength);

bool parse_string_clock(State* state, const char strToken[], int strLength);

bool parse_string_turns(State* state, const char strToken[], int strLength);

bool parse_string_passant(State* state, const char strToken[], int strLength);

bool parse_string_point(Point* point, const char string[], int strLength);

bool parse_string_castles(State* state, const char strToken[], int strLength);

bool parse_castle_symbol(int* castle, char symbol);

bool parse_string_board(Piece* board, const char strToken[], int strLength);

bool parse_board_ranks(Piece* board, char* strArray[]);

bool parse_board_files(Piece* board, int rank, const char string[], int strLength);

bool parse_board_symbol(Piece* board, int rank, int* file, char symbol);

bool parse_board_blanks(Piece* board, int rank, int* file, int blanks);

bool parse_board_piece(Piece* piece, char symbol);

char chess_piece_symbol(Piece piece);

#endif
