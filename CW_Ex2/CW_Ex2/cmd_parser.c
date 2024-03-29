
#include "error_mgr.h"
#include "init_regex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_flags(bool flags_array[]);
int load_flags_and_return_index(int arg_num, char** args, Regex_And_Flags* regex_and_flags);
Flag load_flag_and_update_index(char **args, int *p_index, Regex_And_Flags *my_regex_and_flags);
int get_flag_index(const char *current_flag);

Error_Code_t parse_cmd_args(int arg_num, char **args, Regex_And_Flags **p_regex_and_flags, char **p_expression,
                            char **p_file_name)
{
  Error_Code_t status = SUCCESS_CODE;
  Regex_And_Flags *regex_and_flags;
  int arg_index;

  regex_and_flags = (Regex_And_Flags *)calloc(1, sizeof(Regex_And_Flags));

  status = check_mem_alloc(regex_and_flags, __FILE__, __LINE__, __func__);

  if (status != SUCCESS_CODE) {
    return status;
  }
  initialize_flags(regex_and_flags->flags);

  arg_index = load_flags_and_return_index(arg_num, args, regex_and_flags);

  *p_expression = args[arg_index];

  arg_index++;

  if (arg_index <= arg_num - 1) {
    *p_file_name = args[arg_index];
  }

  *p_regex_and_flags = regex_and_flags;

  return SUCCESS_CODE;
}

void initialize_flags(bool flags_array[])
{
  Flag current_flag;

  for (current_flag = FLAGS_START; current_flag < FLAGS_END; current_flag++) {
    flags_array[current_flag] = false;
  }
}

int load_flags_and_return_index(int arg_num, char** args, Regex_And_Flags* regex_and_flags)
{
    Flag current_flag;
    int arg_index = 1;

    while (arg_index < arg_num) {
        current_flag = load_flag_and_update_index(args, &arg_index, regex_and_flags);

        if (current_flag == NOT_A_FLAG) {
            break;
        }
    }
    return arg_index;
}

Flag load_flag_and_update_index(char **args, int *p_index, Regex_And_Flags *my_regex_and_flags)
{
  Flag current_flag = get_flag_index(args[*p_index]);

  if (current_flag == NOT_A_FLAG) {
    return NOT_A_FLAG;
  }

  my_regex_and_flags->flags[current_flag] = true;

  if (current_flag == A_FLAG) {
    my_regex_and_flags->A_flag_value = atoi(args[*p_index + 1]);
    (*p_index)++;
  }

  (*p_index)++;
  return current_flag;
}

int get_flag_index(const char *current_flag)
{
  Flag index;
  for (index = FLAGS_START; index < FLAGS_END; index++) {
    if (strcmp(current_flag, FLAGS_STR_ARRAY[index]) == 0) {
      return index;
    }
  }
  return NOT_A_FLAG;
}
