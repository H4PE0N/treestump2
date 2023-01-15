
#include "../Header-Files-Folder/engine-include-file.h"

uint64_t HASH_MATRIX[64][12];

Entry* create_hash_table(int tableSize)
{
	Entry* hashTable = malloc(sizeof(Entry) * tableSize);

	for(int index = 0; index < tableSize; index += 1)
	{
		hashTable[index] = (Entry) {.hash = 0, .depth = 0, .score = 0, .flag = 0};
	}
	return hashTable;
}

void create_hash_matrix(uint64_t hashMatrix[BOARD_POINTS][12])
{
	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		create_pieces_hashes(hashMatrix, point);
	}
}

void create_pieces_hashes(uint64_t hashMatrix[BOARD_POINTS][12], Point point)
{
	for(int index = 0; index < 12; index += 1)
	{
		uint64_t random64bit = create_random_uint64(0, (UINT64_MAX - 1));

		hashMatrix[point][index] = random64bit;
	}
}

uint64_t create_random_uint64(uint64_t minimum, uint64_t maximum)
{
	return (rand() % (maximum - minimum + 1) + minimum);
}

uint64_t create_zobrist_hash(uint64_t* hashMatrix[], const Piece board[], State state)
{
	uint64_t zobristHash = 0;
	for(Point point = 0; point < BOARD_POINTS; point += 1)
	{
		if(!chess_piece_exists(board[point])) continue;

		Type type = board[point].type;
		Team team = board[point].team;

		int pieceIndex = ((type - 1) * 2 + (team - 1));

		zobristHash ^= hashMatrix[point][pieceIndex];
	}
	return zobristHash;
}
