#define _CRT_SECURE_NO_WARNINGS

#include "my_grep.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Line_Descriptor {
  char* line;
  int line_counter;
  int byte_counter;
} Line_Descriptor;

void update_line_descriptor(Line_Descriptor* line_desc, char* line_buffer);
bool check_if_matching_line(Line_Descriptor* line_desc, Regex_And_Flags* my_regex_and_flags);
bool is_matching_expression_at_place(char* line, Regex_Block* regex_blocks, int regex_block_num, bool* flags);
void print_if_matching(Line_Descriptor* line_desc, bool is_matching, bool* flags);
bool compare_chars(const char first_char, const char second_char, bool is_case_insensitive);
bool compare_strings(const char* first_str, const char* second_str, bool is_case_insensitive);

void grep_execute_on_stream(FILE* input_stream, Regex_And_Flags* my_regex_and_flags)
{
  Line_Descriptor line_desc = {NULL, 0, 0};
  size_t line_size = 0;
  char* line = NULL;
  bool is_matching_line;

  ssize_t getline_status = getline(&line, &line_size, input_stream);

  while (getline_status >= 0) {
    update_line_descriptor(&line_desc, line);

    is_matching_line = check_if_matching_line(&line_desc, my_regex_and_flags);
    print_if_matching(&line_desc, is_matching_line, my_regex_and_flags->flags);

    getline_status = getline(&line, &line_size, input_stream);
  }
  free(line);
}

bool check_if_matching_line(Line_Descriptor* line_desc, Regex_And_Flags* my_regex_and_flags)
{
  char* line = line_desc->line;
  bool is_matching = false;
  size_t i;
  for (i = 0; i < strlen(line_desc->line); i++) {
    is_matching = is_matching_expression_at_place(line + i, my_regex_and_flags->regex_array,
                                                  my_regex_and_flags->regex_array_len, my_regex_and_flags->flags);

    if (is_matching)
      break;
  }

  if (my_regex_and_flags->flags[V_FLAG])
    return (!is_matching);

  return is_matching;
}

bool is_matching_expression_at_place(char* line, Regex_Block* regex_blocks, int regex_block_num, bool* flags)
{
  if (regex_block_num == 0)
    return true;

  if (*line == '\0')
    return false;

  switch (regex_blocks->type) {
    case REGEX_TYPE_DOT:
      return is_matching_expression_at_place(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

    case REGEX_TYPE_REGULAR_CHAR:
      if (compare_chars(*line, regex_blocks->regex_block_contents.regular_char, flags[I_FLAG]) == false)
        return false;
      return is_matching_expression_at_place(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

    case REGEX_TYPE_PARENTHESES:
      // TODO
      break;

    case REGEX_TYPE_BRACKETS:
      // TODO
      break;
  }
  return true;
}

void print_if_matching(Line_Descriptor* line_desc, bool is_matching, bool* flags)
{
  if (is_matching == false)
    return;

  if (flags[B_FLAG])
    printf("%ld: %s", line_desc->byte_counter - strlen(line_desc->line), line_desc->line);

  else if (flags[N_FLAG])
    printf("%d: %s", line_desc->line_counter, line_desc->line);

  else if (flags[C_FLAG])
    printf("%d\n", line_desc->line_counter);

  else
    printf("%s", line_desc->line);
}

void update_line_descriptor(Line_Descriptor* line_desc, char* line_buffer)
{
  int line_counter = 0;
  int bytes_counter = 0;

  line_counter = line_desc->line_counter + 1;
  bytes_counter = line_desc->byte_counter + strlen(line_buffer);

  line_desc->line = line_buffer;
  line_desc->line_counter = line_counter;
  line_desc->byte_counter = bytes_counter;
}

bool compare_strings(const char* first_str, const char* second_str, bool is_case_insensitive)
{
  if (is_case_insensitive)
    return (strcasecmp(first_str, second_str) == 0);

  return (strcmp(first_str, second_str) == 0);
}

bool compare_chars(const char first_char, const char second_char, bool is_case_insensitive)
{
  if (is_case_insensitive)
    return (tolower(first_char) == tolower(second_char));

  return (first_char == second_char);
}
