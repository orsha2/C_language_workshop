#define _CRT_SECURE_NO_WARNINGS

#include "cmd_parser.h"
#include "error_mgr.h"
#include "init_regex.h"
#include "my_grep.h"
#include <stdio.h>
#include <stdlib.h>

Error_Code_t initialize_input_stream(char *file_name, FILE **p_input_stream);
void free_main_resources(FILE *input_stream, Regex_And_Flags *pattern_and_flags);
void free_parentheses_block(Parentheses *parentheses_block);

int main(int argc, char *argv[])
{
  Error_Code_t status;

  FILE *input_stream = NULL;
  char *file_name = NULL;
  char *expression;
  Regex_And_Flags *my_regex_and_flags = NULL;

  status = check_argc_value_range(argc);

  if (status != SUCCESS_CODE) {
    goto main_exit;
  }
  status = parse_cmd_args(argc, argv, &my_regex_and_flags, &expression, &file_name);

  if (status != SUCCESS_CODE) {
    goto main_exit;
  }
  status = initialize_regex_array(expression, &my_regex_and_flags->regex_array, &(my_regex_and_flags->regex_array_len));

  if (status != SUCCESS_CODE) {
    goto main_exit;
  }
  status = initialize_input_stream(file_name, &input_stream);

  if (status != SUCCESS_CODE) {
    goto main_exit;
  }
  grep_execute_on_stream(input_stream, my_regex_and_flags);

main_exit:
  free_main_resources(input_stream, my_regex_and_flags);

  return (int)status;
}

Error_Code_t initialize_input_stream(char *file_name, FILE **p_input_stream)
{
  Error_Code_t status = SUCCESS_CODE;
  if (file_name == NULL) {
    *p_input_stream = stdin;
  } else {
    *p_input_stream = fopen(file_name, "r");

    status = check_file_opening(*p_input_stream, __FILE__, __LINE__, __func__);
  }

  return status;
}

void free_main_resources(FILE *input_stream, Regex_And_Flags *my_regex_and_flags)
{
  if (input_stream != NULL && input_stream != stdin) {
    fclose(input_stream);
  }
  if (my_regex_and_flags == NULL) {
    return;
  }
  Regex_Block *regex_array = my_regex_and_flags->regex_array;
  int i;

  for (i = 0; i < my_regex_and_flags->regex_array_len; i++) {
    if (regex_array[i].type != REGEX_TYPE_PARENTHESES) {
      continue;
    }
    free_parentheses_block(&(regex_array[i].regex_block_contents.parentheses_block));
  }

  if (regex_array != NULL) {
    free(regex_array);
  }
  if (my_regex_and_flags != NULL) {
    free(my_regex_and_flags);
  }
}

void free_parentheses_block(Parentheses *parentheses_block)
{
  char *parenthesis_contents = parentheses_block->left_side;

  if (parenthesis_contents != NULL) {
    free(parenthesis_contents);
  }
}
