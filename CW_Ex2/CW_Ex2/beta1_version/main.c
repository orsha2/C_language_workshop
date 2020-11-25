#define _CRT_SECURE_NO_WARNINGS

#include "cmd_parser.h"
#include "error_mgr.h"
#include "init_regex.h"
#include "my_grep.h"
#include <stdio.h>
#include <stdlib.h>

Error_Code_t initialize_input_stream(char *file_name, FILE **p_f_input);
void free_main_resources(FILE *input_stream,
                         Regex_And_Flags *pattern_and_flags);

int main(int argc, char *argv[]) {
  Error_Code_t status;

  FILE *input_stream = NULL;
  char *file_name = NULL;
  char *expression;
  Regex_And_Flags *my_regex_and_flags = NULL;

  if (argc < 2) {
    print_error(MSG_ERR_NUM_ARGS, __FILE__, __LINE__, __func__);
    status = ARGS_NUM_ERROR;
    goto main_exit;
  }

  status =
      parse_cmd_args(argc, argv, &my_regex_and_flags, &expression, &file_name);

  if (status != SUCCESS_CODE)
    goto main_exit;

  status = initialize_regex_array(expression, &my_regex_and_flags->regex_array,
                                  &(my_regex_and_flags->regex_array_len),
                                  my_regex_and_flags->flags[E_FLAG]);

  if (status != SUCCESS_CODE)
    goto main_exit;

  status = initialize_input_stream(file_name, &input_stream);

  if (status != SUCCESS_CODE)
    goto main_exit;

  status = grep_execute_on_stream(input_stream, my_regex_and_flags);

main_exit:

  free_main_resources(input_stream, my_regex_and_flags);

  return status;
}

Error_Code_t initialize_input_stream(char *file_name, FILE **p_f_input) {

  if (file_name == NULL)
    *p_f_input = stdin;

  else {
    *p_f_input = fopen(file_name, "r");

    if (*p_f_input == NULL) {
      print_error(MSG_ERR_CANNOT_OPEN_FILE, __FILE__, __LINE__, __func__);
      return FILE_OPEN_FAILED;
    }
  }

  return SUCCESS_CODE;
}

void free_main_resources(FILE *input_stream,
                         Regex_And_Flags *my_regex_and_flags) {
  if (input_stream != NULL)
    fclose(input_stream);

  if (my_regex_and_flags == NULL)
    return;

  Regex_Block *regex_array = my_regex_and_flags->regex_array;
  for (int i = 0; i < my_regex_and_flags->regex_array_len; i++) {
    if (regex_array->type != REGEX_TYPE_PARENTHESES)
      continue;
    if (regex_array->regex_block_contents.parentheses_block.left_side != NULL)
      free(regex_array->regex_block_contents.parentheses_block.left_side);
    if (regex_array->regex_block_contents.parentheses_block.right_side != NULL)
      free(regex_array->regex_block_contents.parentheses_block.right_side);
  }
  free(regex_array);
  free(my_regex_and_flags);
}
