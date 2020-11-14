#ifndef REGEX_HANDLER_H
#define REGEX_HANDLER_H

#include <stdbool.h>

#define FLAGS_NUM 8 
#define NOT_A_FLAG -1 

extern const char* FLAGS_STR_ARRAY[];

typedef enum _flag {
	FLAGS_START = 0,
	I_FLAG = FLAGS_START, V_FLAG, C_FLAG, N_FLAG, X_FLAG, B_FLAG, E_FLAG, A_FLAG,
	FLAGS_END
} flag;

typedef struct _LineDescriptor {
	char* line;
	int   line_counter;
	int   byte_counter;

} LineDescriptor;

typedef struct _ExpressionAndFlags {
	char* expression;

	bool flags[FLAGS_NUM];

	int A_flag_value;

} ExpressionAndFlags;



#endif