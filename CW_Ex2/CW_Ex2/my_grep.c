
#include "my_grep.h"
#include "error_mgr.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Line_Descriptor {
  char *line;
  int line_counter;
  int byte_counter;
} Line_Descriptor;

bool check_if_matching_line(Line_Descriptor *line_desc, Regex_And_Flags *my_regex_and_flags);
bool is_matching_expression_at_place(char *line, Regex_Block *regex_blocks, int regex_block_num, bool *flags);
bool check_x_flag_and_start_of_line(bool x_flag, int line_index);
bool check_x_flag_and_end_of_line(bool x_flag, char current_char);
bool check_if_print_and_update_lines_to_print(bool is_matching_line, bool *p_print_separator, int *p_lines_to_print,
                                              Regex_And_Flags *my_regex_and_flags);
bool check_if_line_starting_with_substring(const char *line, const char *substring, bool is_case_insensitive);
bool check_if_bracket_block_matching(char current_char, Bracket bracket_block, bool is_case_insensitive);
bool check_if_parentheses_and_rest_of_line_match(char *line, Regex_Block *regex_blocks, int regex_block_num,
                                                 bool *flags);
bool compare_chars(const char first_char, const char second_char, bool is_case_insensitive);
void update_lines_to_print_for_a_flag(bool is_matching_line, int* p_lines_to_print, bool* p_print_separator, int A_flag_value);
void grep_printer(Line_Descriptor *line_desc, bool is_matching, bool *flags, bool is_first_matching_block, bool print_separator);
void print_lines_block_separator_if_new_block(bool is_matching, const bool *flags, bool is_first_matching_block, bool print_separator);
void print_matching_line_counter_if_c_flag(bool c_flag, int matching_lines_amount);
void update_line_descriptor(Line_Descriptor *line_desc, char *line_buffer);
char to_lowercase_if_alpha(char current_char);

static const char *LINES_BLOCK_SEPARATOR = "--";
static const char MATCHING_LINE_SEPARATOR = ':';
static const char NOT_MATCHING_LINE_SEPARATOR = '-';
static const int NON_OVERLAPPING_BLOCKS = -1; 


void grep_execute_on_stream(FILE *input_stream, Regex_And_Flags *my_regex_and_flags)
{
  Line_Descriptor line_desc = {NULL, 0, 0};
  char *line = NULL;
  bool is_matching_line, to_print;
  bool is_first_matching_block = true, print_separator = false;
  size_t line_size = 0;
  int matching_line_counter = 0, lines_to_print = 0;

  ssize_t status = getline(&line, &line_size, input_stream);

  while (status >= 0) {
    update_line_descriptor(&line_desc, line);

    is_matching_line = check_if_matching_line(&line_desc, my_regex_and_flags);

    to_print = check_if_print_and_update_lines_to_print(is_matching_line, &print_separator, &lines_to_print, my_regex_and_flags);

    if (to_print) {
      grep_printer(&line_desc, is_matching_line, my_regex_and_flags->flags, is_first_matching_block, print_separator);
    }

    if (is_matching_line) {
      is_first_matching_block = false;
      matching_line_counter++;
    }

    status = getline(&line, &line_size, input_stream);
  }
  print_matching_line_counter_if_c_flag(my_regex_and_flags->flags[C_FLAG], matching_line_counter);

  free(line);
}

bool check_if_print_and_update_lines_to_print(bool is_matching_line, bool* p_print_separator, int* p_lines_to_print,
    Regex_And_Flags* my_regex_and_flags)
{
    if (my_regex_and_flags->flags[C_FLAG]) {
        return false;
    }

    if (my_regex_and_flags->flags[A_FLAG] == false) {
        return is_matching_line;
    }

    update_lines_to_print_for_a_flag(is_matching_line, p_lines_to_print, 
                                     p_print_separator, my_regex_and_flags->A_flag_value); 

    return (*p_lines_to_print >= 0);
}

bool check_if_matching_line(Line_Descriptor *line_desc, Regex_And_Flags *my_regex_and_flags)
{
  char *line = line_desc->line;
  bool is_matching = false;
  size_t i;

  for (i = 0; i < strlen(line_desc->line); i++) {
    if (check_x_flag_and_start_of_line(my_regex_and_flags->flags[X_FLAG], i)) {
      is_matching = false;
      break;
    }
    is_matching = is_matching_expression_at_place(line + i, my_regex_and_flags->regex_array,
                                                  my_regex_and_flags->regex_array_len, my_regex_and_flags->flags);

    if (is_matching) {
      break;
    }
  }

  if (my_regex_and_flags->flags[V_FLAG]) {
    return (!is_matching);
  }
  return is_matching;
}

bool is_matching_expression_at_place(char *line, Regex_Block *regex_blocks, int regex_block_num, bool *flags)
{
  if (regex_block_num == 0) {
    if (check_x_flag_and_end_of_line(flags[X_FLAG], *line)) {
      return false;
    }

    return true;
  }

  if (*line == '\0' || *line == '\n') {
    return false;
  }
  switch (regex_blocks->type) {
    case REGEX_TYPE_DOT:
      return is_matching_expression_at_place(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

    case REGEX_TYPE_REGULAR_CHAR:
      if (compare_chars(*line, regex_blocks->regex_block_contents.regular_char, flags[I_FLAG]) == false) {
        return false;
      }
      return is_matching_expression_at_place(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

    case REGEX_TYPE_BRACKETS:
      if (check_if_bracket_block_matching(*line, regex_blocks->regex_block_contents.bracket_block, flags[I_FLAG]) == false) {
        return false;
      }
      return is_matching_expression_at_place(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

    case REGEX_TYPE_PARENTHESES:
      return check_if_parentheses_and_rest_of_line_match(line, regex_blocks, regex_block_num, flags);
  }
  return false;
}

bool check_if_parentheses_and_rest_of_line_match(char *line, Regex_Block *regex_blocks, int regex_block_num,
                                                 bool *flags)
{
  bool is_left_side_matching = false, is_right_side_matching = false;

  Regex_Block_Contents *block_contents = &(regex_blocks->regex_block_contents);

  char *left_side = block_contents->parentheses_block.left_side;
  char *right_side = block_contents->parentheses_block.right_side;

  if (check_if_line_starting_with_substring(line, right_side, flags[I_FLAG])) {
    is_right_side_matching =
        is_matching_expression_at_place(line + strlen(right_side), regex_blocks + 1, regex_block_num - 1, flags);
  }

  if (check_if_line_starting_with_substring(line, left_side, flags[I_FLAG])) {
    is_left_side_matching =
        is_matching_expression_at_place(line + strlen(left_side), regex_blocks + 1, regex_block_num - 1, flags);
  }

  return is_left_side_matching || is_right_side_matching;
}

bool check_x_flag_and_start_of_line(bool x_flag, int line_index) { return (x_flag && line_index > 0); }

bool check_x_flag_and_end_of_line(bool x_flag, char current_char)
{
  return (x_flag && (current_char != '\0' && current_char != '\n'));
}

bool check_if_line_starting_with_substring(const char *line, const char *substring, bool is_case_insensitive)
{
  while (*line != '\0' && *substring != '\0') {
    if (compare_chars(*line, *substring, is_case_insensitive) == false) {
      return false;
    }
    line++;
    substring++;
  }

  if (*substring == '\0') {
    return true;
  }

  return false;
}

bool compare_chars(const char first_char, const char second_char, bool is_case_insensitive)
{
  if (is_case_insensitive) {
    return (to_lowercase_if_alpha(first_char) == to_lowercase_if_alpha(second_char));
  }
  return (first_char == second_char);
}

bool check_if_bracket_block_matching(char current_char, Bracket bracket_block, bool is_case_insensitive)
{
    char start_char = bracket_block.bracket_start;
    char end_char = bracket_block.bracket_end;

    if (is_case_insensitive) {
        start_char = to_lowercase_if_alpha(start_char);
        end_char = to_lowercase_if_alpha(end_char);
        current_char = to_lowercase_if_alpha(current_char);
    }

    return (current_char >= start_char && current_char <= end_char);
}

char to_lowercase_if_alpha(char current_char)
{
    if (isalpha(current_char)) {
        return  tolower(current_char);
    }
    return current_char;
}

void update_lines_to_print_for_a_flag(bool is_matching_line, int* p_lines_to_print, bool* p_print_separator, int A_flag_value)
{
    if (is_matching_line) {
        *p_print_separator = (*p_lines_to_print == NON_OVERLAPPING_BLOCKS);
        *p_lines_to_print = A_flag_value;
    }
    else if (*p_lines_to_print >= 0) {
        *p_lines_to_print -= 1;
    }
}

void grep_printer(Line_Descriptor *line_desc, bool is_matching, bool *flags, bool is_first_matching_block, bool print_separator)
{
  char separator = MATCHING_LINE_SEPARATOR;

  if (is_matching == false) {
    separator = NOT_MATCHING_LINE_SEPARATOR;
  }

  print_lines_block_separator_if_new_block(is_matching, flags, is_first_matching_block, print_separator);

  if (flags[N_FLAG]) {
    printf("%d%c", line_desc->line_counter, separator);
  } 
  if (flags[B_FLAG]) {
    printf("%ld%c", line_desc->byte_counter -  strlen(line_desc->line), separator);
  }
  printf("%s", line_desc->line);
}

void print_lines_block_separator_if_new_block(bool is_matching, const bool *flags, bool is_first_matching_block, bool print_separator)
{
  if (is_matching) {
    if (flags[A_FLAG] && (is_first_matching_block == false && print_separator)) {
      printf("%s\n", LINES_BLOCK_SEPARATOR);
    }
  }
}

void print_matching_line_counter_if_c_flag(bool c_flag, int matching_lines_amount)
{
  if (c_flag) {
    printf("%d\n", matching_lines_amount);
  }
}

void update_line_descriptor(Line_Descriptor *line_desc, char *line_buffer)
{
  int line_counter = line_desc->line_counter + 1;
  int bytes_counter = line_desc->byte_counter + strlen(line_buffer);

  line_desc->line = line_buffer;
  line_desc->line_counter = line_counter;
  line_desc->byte_counter = bytes_counter;
}
