﻿
#include <stdio.h>
#include "init_regex.h"
#include "error_mgr.h"
#include <stdlib.h>
#include <string.h>

typedef enum _Char_Type {
  CHAR_REGULAR,
  CHAR_DOT,
  CHAR_PARENTHESES_START,
  CHAR_PARENTHESES_END,
  CHAR_BRACKETS_START,
  CHAR_BRACKETS_END,
  CHAR_BACK_SLASH,
} Char_Type;

const char *FLAGS_STR_ARRAY[] = {"-i", "-v", "-c", "-n", "-x", "-b", "-E", "-A"};

static const int FIRST_CHAR_IN_STR_INDEX = 0;
static const int SECOND_CHAR_IN_STR_INDEX = 1;

Error_Code_t init_regex_block_and_advance_expression(Regex_Block *current_regex_block, char **p_rest_of_expression);
Error_Code_t set_parentheses_block_and_return_status(char **p_parentheses_block_start,
                                                     Regex_Block *current_regex_block);
void set_parentheses_block_contents(Regex_Block_Contents *regex_block_contents, char *left_side, char *right_side);
void set_regular_char_block(char regular_char, Regex_Block *current_regex_block);
char *set_bracket_block(char *bracket_block_start, Regex_Block *current_regex_block);
int get_bracket_block_end(const char *expression, int index);

void strcpy_until_char(char **p_dest, char **p_source, char end_char);
int count_amount_of_regex_blocks(char *expression);
Char_Type classify_char_type(char my_char);


Error_Code_t initialize_regex_array(char *expression, Regex_Block **p_regex_array, int *p_regex_array_len)
{
  Error_Code_t status = SUCCESS_CODE;
  int index, regex_array_len;
  Regex_Block *regex_array;

  regex_array_len = count_amount_of_regex_blocks(expression);
  regex_array = (Regex_Block *)calloc(regex_array_len, sizeof(Regex_Block));

  status = check_mem_alloc(regex_array, __FILE__, __LINE__, __func__);

  if (status != SUCCESS_CODE) {
    return status;
  }
  char *rest_of_expression = expression;

  for (index = 0; index < regex_array_len; index++) {
    status = init_regex_block_and_advance_expression(&(regex_array[index]), &rest_of_expression);

    if (status != SUCCESS_CODE) {
      break;
    }
  }

  *p_regex_array_len = regex_array_len;
  *p_regex_array = regex_array;

  return status;
}

Error_Code_t init_regex_block_and_advance_expression(Regex_Block *current_regex_block, char **p_rest_of_expression)
{
  Error_Code_t status = SUCCESS_CODE;
  Char_Type current_char_type;
  char *rest_of_expression = *p_rest_of_expression;

  current_char_type = classify_char_type(*rest_of_expression);

  switch (current_char_type) {
    case CHAR_DOT:
      current_regex_block->type = REGEX_TYPE_DOT;
      break;

    case CHAR_REGULAR:
      set_regular_char_block(rest_of_expression[FIRST_CHAR_IN_STR_INDEX], current_regex_block);
      break;

    case CHAR_BACK_SLASH:
      set_regular_char_block(rest_of_expression[SECOND_CHAR_IN_STR_INDEX], current_regex_block);
      rest_of_expression++;
      break;

    case CHAR_PARENTHESES_START:
      rest_of_expression++;
      status = set_parentheses_block_and_return_status(&rest_of_expression, current_regex_block);
      break;

    case CHAR_BRACKETS_START:
      rest_of_expression = set_bracket_block(rest_of_expression, current_regex_block);
      break;

    case CHAR_PARENTHESES_END:
    case CHAR_BRACKETS_END:
      break;
  }
  rest_of_expression++;
  *p_rest_of_expression = rest_of_expression;

  return status;
}

void set_regular_char_block(char regular_char, Regex_Block *current_regex_block)
{
  current_regex_block->type = REGEX_TYPE_REGULAR_CHAR;
  current_regex_block->regex_block_contents.regular_char = regular_char;
}

Error_Code_t set_parentheses_block_and_return_status(char **p_parentheses_block_start, Regex_Block *current_regex_block)
{
  Error_Code_t status;
  char *left_side;
  char *right_side;
  current_regex_block->type = REGEX_TYPE_PARENTHESES;

  int size_of_block = get_bracket_block_end(*p_parentheses_block_start, FIRST_CHAR_IN_STR_INDEX);

  char *parentheses_contents = (char *)malloc((size_of_block + 1) * sizeof(char));

  status = check_mem_alloc(parentheses_contents, __FILE__, __LINE__, __func__);

  if (status != SUCCESS_CODE) {
    return status;
  }

  left_side = parentheses_contents;
  strcpy_until_char(&parentheses_contents, p_parentheses_block_start, '|');

  (*p_parentheses_block_start)++;
  right_side = parentheses_contents;
  strcpy_until_char(&parentheses_contents, p_parentheses_block_start, ')');

  set_parentheses_block_contents(&current_regex_block->regex_block_contents, left_side, right_side);

  return SUCCESS_CODE;
}

void strcpy_until_char(char **p_dest, char **p_source, char end_char)
{
  char *source = *p_source;
  char *dest = *p_dest;

  while (*source != end_char && *source != '\0') {
    *dest = *source;
    source++;
    dest++;
  }

  *dest = '\0';
  dest++;

  *p_source = source;
  *p_dest = dest;
}

void set_parentheses_block_contents(Regex_Block_Contents *regex_block_contents, char *left_side, char *right_side)
{
  regex_block_contents->parentheses_block.left_side = left_side;
  regex_block_contents->parentheses_block.right_side = right_side;
}

char *set_bracket_block(char *bracket_block_start, Regex_Block *current_regex_block)
{
  int bracket_end_index = get_bracket_block_end(bracket_block_start, FIRST_CHAR_IN_STR_INDEX);

  current_regex_block->type = REGEX_TYPE_BRACKETS;
  current_regex_block->regex_block_contents.bracket_block.bracket_start = bracket_block_start[SECOND_CHAR_IN_STR_INDEX];

  current_regex_block->regex_block_contents.bracket_block.bracket_end = bracket_block_start[bracket_end_index - 1];

  bracket_block_start += bracket_end_index;

  return bracket_block_start;
}

int count_amount_of_regex_blocks(char *expression)
{
  int block_counter = 0;
  size_t current_char_index = 0;
  char current_char;
  Char_Type current_char_type;

  while (current_char_index < strlen(expression)) {
    current_char = expression[current_char_index];
    current_char_type = classify_char_type(current_char);

    switch (current_char_type) {
      case CHAR_BACK_SLASH:
        block_counter++;
        current_char_index++;
        break;

      case CHAR_REGULAR:
      case CHAR_DOT:
        block_counter++;
        break;

      case CHAR_PARENTHESES_START:
      case CHAR_BRACKETS_START:
        block_counter++;
        current_char_index = get_bracket_block_end(expression, current_char_index);
        break;

      case CHAR_PARENTHESES_END:
      case CHAR_BRACKETS_END:
        break;
    }
    current_char_index++;
  }
  return block_counter;
}

int get_bracket_block_end(const char *expression, int index)
{
  char current_char;
  Char_Type current_char_type; 

  do {
    current_char = expression[index];
    current_char_type = classify_char_type(current_char);
    index++;

  } while (current_char != '\0' && current_char_type != CHAR_PARENTHESES_END && current_char_type != CHAR_BRACKETS_END);

  index--;
  return index;
}

Char_Type classify_char_type(char my_char)
{
  switch (my_char) {
    case '(':
      return CHAR_PARENTHESES_START;

    case '[':
      return CHAR_BRACKETS_START;

    case ')':
      return CHAR_PARENTHESES_END;

    case ']':
      return CHAR_BRACKETS_END;

    case '\\':
      return CHAR_BACK_SLASH;

    case '.':
      return CHAR_DOT;
  }
  return CHAR_REGULAR;
}
