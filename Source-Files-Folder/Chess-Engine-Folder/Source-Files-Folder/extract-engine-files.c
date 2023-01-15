
#include "../Header-Files-Folder/engine-include-file.h"

bool extract_score_matrix_t(int scoreMatrix[BOARD_RANKS][BOARD_FILES], FILE* filePointer)
{
	char lineBuffer[64]; char* scoreStrings[BOARD_FILES];
	for(int rank = 0; rank < BOARD_RANKS; rank += 1)
	{
		if(fgets(lineBuffer, 64, filePointer) == NULL) return false;

		if(!split_string_delim(scoreStrings, lineBuffer, strlen(lineBuffer), " ", BOARD_FILES)) return false;

		for(int file = 0; file < BOARD_FILES; file += 1)
		{
			scoreMatrix[rank][file] = atoi(scoreStrings[file]);
		}
		free_array_strings(scoreStrings, BOARD_FILES);
	}
	return true;
}

bool extract_score_matrix(int scoreMatrix[BOARD_RANKS][BOARD_FILES], const char filePath[])
{
	FILE* filePointer = fopen(filePath, "r");
	if(filePointer == NULL) return false;

	bool result = extract_score_matrix_t(scoreMatrix, filePointer);

	fclose(filePointer); return result;
}

bool type_matrix_filepath(char* filePath, Type type)
{
	if(!piece_type_exists(type)) return false;

	sprintf(filePath, "%s/%s-score-matrix.txt", ENGINE_FILES_FOLDER, TYPE_WORDS[type]);

	return true;
}

bool extract_score_matrixs(int scoreMatrixs[PIECE_TYPE_SPAN][BOARD_RANKS][BOARD_FILES])
{
	char filePath[128];
	for(Type type = TYPE_PAWN; type <= TYPE_KING; type += 1)
	{
		if(!type_matrix_filepath(filePath, type)) return false;

		if(!extract_score_matrix(scoreMatrixs[type], filePath)) return false;
	}
	return true;
}
