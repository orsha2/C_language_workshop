#ifndef REGEX_HANDLER_H
#define REGEX_HANDLER_H

#include "error_mgr.h"
#include <stdbool.h>

#define FLAGS_NUM 8

extern const char *FLAGS_STR_ARRAY[];

typedef enum _Flag {
  FLAGS_START = 0,
  I_FLAG = FLAGS_START,
  V_FLAG,
  C_FLAG,
  N_FLAG,
  X_FLAG,
  B_FLAG,
  E_FLAG,
  A_FLAG,
  FLAGS_END,
  NOT_A_FLAG
} Flag;

typedef enum _Regex_Block_Type {
  REGEX_TYPE_DOT,
  REGEX_TYPE_REGULAR_CHAR,
  REGEX_TYPE_PARENTHESES,
  REGEX_TYPE_BRACKETS
} Regex_Block_Type;

typedef struct _Parentheses {
  char *left_side;
  char *right_side;
} Parentheses;

typedef struct _Bracket {
  char bracket_start;
  char bracket_end;
} Bracket;

typedef union _Regex_Block_Contents {
  char regular_char;
  Parentheses parentheses_block;
  Bracket bracket_block;

} Regex_Block_Contents;

typedef struct _Regex_Block {
  Regex_Block_Type type;
  Regex_Block_Contents regex_block_contents;

} Regex_Block;

typedef struct _Regex_And_Flags {

  Regex_Block *regex_array;
  int regex_array_len;

  bool flags[FLAGS_NUM];
  int A_flag_value;

} Regex_And_Flags;

Error_Code_t initialize_regex_array(char *expression, Regex_Block **p_regex_array, int *p_regex_array_len,
                                    bool is_E_flag);

#endif