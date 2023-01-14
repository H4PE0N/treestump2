
#include "../Header-Files-Folder/englog-include-file.h"

bool split_string_delim(char* strArray[], const char string[], int strLength, const char delim[], int amount)
{
	if(amount < 1) return false;

	alloc_array_strings(strArray, amount, strLength);

	char stringCopy[strLength + 1]; strcpy(stringCopy, string);

	if(!split_string_delim_t(strArray, stringCopy, delim, amount))
	{
		free_array_strings(strArray, amount); return false;
	}
	return true;
}

bool split_string_delim_t(char* strArray[], char* stringCopy, const char delim[], int amount)
{
	char* stringToken = NULL;

	if((stringToken = strtok(stringCopy, delim)) == NULL) return false;

	strcpy(strArray[0], stringToken);

	for(int index = 1; index < amount; index += 1)
	{
		if((stringToken = strtok(NULL, delim)) == NULL) return false;

		strcpy(strArray[index], stringToken);
	}
	return true;
}

bool merge_string_delim(char* string, char* strArray[], int amount, const char delim[])
{
	if(amount < 1) return false;

	for(int index = 0; index < amount; index += 1)
	{
		strcat(string, strArray[index]);

		if(index < (amount - 1)) strcat(string, delim);
	}
	return true;
}

void alloc_array_strings(char* strArray[], int amount, int strLength)
{
	for(int index = 0; index < amount; index += 1)
	{
		strArray[index] = create_char_string(strLength);
	}
}

void free_array_strings(char* strArray[], int amount)
{
	for(int index = 0; index < amount; index += 1)
	{
		free(strArray[index]);
	}
}

int string_symbol_index(const char string[], int strLength, char symbol)
{
	for(int index = 0; index < strLength; index += 1)
	{
		if(symbol == string[index]) return index;
	}
	return INDEX_NONE;
}

char* create_char_string(int strLength)
{
	char* string = malloc(sizeof(char) * (strLength + 1));

	memset(string, '\0', sizeof(char) * (strLength + 1));

	return string;
}

bool parse_token_quotes(char* result, const char string[], const char token[])
{
  char strCpy[strlen(string) + 1]; strcpy(strCpy, string);

  char* strPoint;
  if(!(strPoint = strstr(strCpy, token))) return false;

  if(strtok(strPoint, "\"") == NULL) return false;

  char* strToken;
  if((strToken = strtok(NULL, "\"")) == NULL) return false;

  strcpy(result, strToken); return true;
}

bool parse_spaced_token(char* result, const char string[], const char token[])
{
  char strCopy[strlen(string) + 1]; strcpy(strCopy, string);

  char* strPoint;
  if(!(strPoint = strstr(strCopy, token))) return false;

  if(strtok(strPoint, " ") == NULL) return false;

  char* strToken;
  if((strToken = strtok(NULL, " ")) == NULL) return false;

  strcpy(result, strToken); return true;
}
