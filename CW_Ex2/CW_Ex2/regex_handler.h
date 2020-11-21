#ifndef REGEX_HANDLER_H
#define REGEX_HANDLER_H

#include <stdbool.h>

#define FLAGS_NUM 8 

extern const char* FLAGS_STR_ARRAY[];

typedef enum _flag {
	FLAGS_START = 0,
	I_FLAG = FLAGS_START, V_FLAG, C_FLAG, N_FLAG, X_FLAG, B_FLAG, E_FLAG, A_FLAG,
	FLAGS_END,
	NOT_A_FLAG
} flag;

typedef enum _regex_block_type {
	TYPE_DOT,
	TYPE_REGULAR_CHAR,
	TYPE_PARENTHESES,
	TYPE_SQUARE_BRACKETS
} regex_type;


typedef struct _parentheses
{
	char* left_side;
	char* right_side;
}parentheses;


typedef struct _bracket
{
	char bracket_start;
	char bracket_end;
}bracket;


typedef union _regex_block
{
	char regular_char;
	parentheses parentheses_block;
	bracket bracket_block;

}regex_block;

typedef struct _regex
{
	regex_type type;
	regex_block regex_block;

}regex;

typedef struct _regex_and_flags {
	
	regex* regex_array;
	int regex_array_len;
	bool flags[FLAGS_NUM];

	int A_flag_value;

} regex_and_flags;


typedef struct _line_descriptor {
	char* line;
	int   line_counter;
	int   byte_counter;
} line_descriptor;


#endif