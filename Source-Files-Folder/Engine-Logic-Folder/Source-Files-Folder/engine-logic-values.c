
#include "../Header-Files-Folder/englog-include-file.h"

const int INDEX_NONE = -1;

const int BOARD_RANKS = 8;
const int BOARD_FILES = 8;
const int BOARD_POINTS = 64;

const int TYPE_SPAN = 7;
const int TEAM_SPAN = 3;

const int BLACK_MOVE_VALUE = +1;
const int WHITE_MOVE_VALUE = -1;

const Point WHITE_KING_POINT = 0b111100;
const Point BLACK_KING_POINT = 0b000100;

const Point BROOK_QSIDE_POINT = 0b000000;
const Point BROOK_KSIDE_POINT = 0b000111;
const Point WROOK_QSIDE_POINT = 0b111000;
const Point WROOK_KSIDE_POINT = 0b111111;

const int KSIDE_OFFSET = +2;
const int QSIDE_OFFSET = -2;

const int WHITE_START_RANK = 0b111;
const int BLACK_START_RANK = 0b000;

const int WHITE_PAWN_RANK = 0b110;
const int BLACK_PAWN_RANK = 0b001;

const int WHITE_PASSANT_RANK = 0b101;
const int BLACK_PASSANT_RANK = 0b010;

const int KING_FILE = 0b100;

const Piece PIECE_NONE = {.type = TYPE_NONE, .team = TEAM_NONE};

const Move MOVE_NONE = {.start = -1, .stop = -1, .flag = MFLAG_NONE};

const int WHITE_KSIDE = 0b1000;
const int WHITE_QSIDE = 0b0100;
const int BLACK_KSIDE = 0b0010;
const int BLACK_QSIDE = 0b0001;

const int EMPTY_CASTLE = 0b0000;
