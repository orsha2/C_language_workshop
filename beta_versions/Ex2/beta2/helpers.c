#include "helpers.h"
#include <stdio.h>

void print_expression_and_flags(Regex_And_Flags *my_regex_and_flags,
                                char *expression) {
  printf("expression = %s\n", expression);

  Flag j;
  printf("A_flag_value = %d\n", my_regex_and_flags->A_flag_value);

  for (j = FLAGS_START; j < FLAGS_END; j++) {
    printf("%s = %d \n", FLAGS_STR_ARRAY[j], my_regex_and_flags->flags[j]);
  }
}

void print_regex(Regex_And_Flags *my_regex_and_flags) {
  Regex_Block *reg_array = my_regex_and_flags->regex_array;
  int len = my_regex_and_flags->regex_array_len;

  for (int j = 0; j < len; j++) {
    switch (reg_array[j].type) {
    case REGEX_TYPE_DOT:
      printf(".");
      break;

    case REGEX_TYPE_REGULAR_CHAR:
      printf("%c", (reg_array + j)->regex_block_contents.regular_char);
      break;

    case REGEX_TYPE_PARENTHESES:
      printf(
          "(%s|%s)",
          (reg_array + j)->regex_block_contents.parentheses_block.left_side,
          (reg_array + j)->regex_block_contents.parentheses_block.right_side);
      break;

    case REGEX_TYPE_BRACKETS:
      printf("[%c-%c]",
             (reg_array + j)->regex_block_contents.bracket_block.bracket_start,
             (reg_array + j)->regex_block_contents.bracket_block.bracket_end);
      break;
    }
  }
  printf("\n");
}
