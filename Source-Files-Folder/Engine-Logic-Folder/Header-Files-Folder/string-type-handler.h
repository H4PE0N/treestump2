
#ifndef STRING_TYPE_HANDLER_H
#define STRING_TYPE_HANDLER_H

bool split_string_delim(char* strArray[], const char string[], int strLength, const char delim[], int amount);

bool split_string_delim_t(char* strArray[], char* stringCopy, const char delim[], int amount);

void alloc_array_strings(char* strArray[], int amount, int strLength);

void free_array_strings(char* strArray[], int amount);

int string_symbol_index(const char string[], int strLength, char symbol);

bool merge_string_delim(char* string, char* strArray[], int amount, const char delim[]);

char* create_char_string(int strLength);

bool parse_spaced_token(char* result, const char string[], const char token[]);

bool parse_token_quotes(char* result, const char string[], const char token[]);

#endif
