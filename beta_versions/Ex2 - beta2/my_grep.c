#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_grep.h"
#include "error_mgr.h"

typedef struct _Line_Descriptor {
    char* line;
    int line_counter;
    int byte_counter;
} Line_Descriptor;


void update_line_descriptor(Line_Descriptor* line_desc, char* line_buffer);
bool check_if_matching_line(Line_Descriptor* line_desc, Regex_And_Flags* my_regex_and_flags);
bool is_matching_expression_at_place(char* line, Regex_Block* regex_blocks, int regex_block_num, bool* flags);
bool check_x_flag_and_start_of_line(bool x_flag, int line_index);
bool check_x_flag_and_end_of_line(bool x_flag, char current_char);
bool check_if_print_and_update_lines_to_print(bool is_matching_line, int* p_lines_to_print, Regex_And_Flags* my_regex_and_flags); 
bool check_if_line_starting_with_substring(const char* line, const char* substring, bool is_case_insensitive); 
bool check_if_char_in_range(char current_char, Bracket bracket_block);
bool check_if_parentheses_and_rest_of_line_match(char* line, Regex_Block* regex_blocks, int regex_block_num, bool* flags);
bool compare_chars(const char first_char, const char second_char, bool is_case_insensitive);
void grep_printer(Line_Descriptor* line_desc, bool is_matching, bool* flags, bool is_first_matching_block);
void print_lines_block_separator_if_new_block(bool is_matching, bool* flags, bool is_first_matching_block);
void handle_c_flag(bool c_flag, int matching_lines_amount);


static const char* LINES_BLOCK_SEPARATOR = "--";
static const char MATCHING_LINE_SEPARATOR = ':';
static const char NOT_MATCHING_LINE_SEPARATOR = '-';


void grep_execute_on_stream(FILE* input_stream, Regex_And_Flags* my_regex_and_flags)
{
    Line_Descriptor line_desc = { NULL, 0, 0 };
    char* line = NULL;
    bool is_matching_line, to_print;
    bool is_first_matching_block = true;
    size_t line_size = 0;
    int matching_line_counter = 0, lines_to_print = 0;

    ssize_t status = getline(&line, &line_size, input_stream);

    while (status >= 0)
    {
        update_line_descriptor(&line_desc, line);

        is_matching_line = check_if_matching_line(&line_desc, my_regex_and_flags);

        matching_line_counter += is_matching_line ? 1 : 0;

        to_print = check_if_print_and_update_lines_to_print(is_matching_line, &lines_to_print, my_regex_and_flags);

        if (to_print)
            grep_printer(&line_desc, is_matching_line, my_regex_and_flags->flags, is_first_matching_block);

        if (is_matching_line)
            is_first_matching_block = false;

        status = getline(&line, &line_size, input_stream);
    }

    handle_c_flag(my_regex_and_flags->flags[C_FLAG], matching_line_counter);
    free(line);
}

bool check_if_print_and_update_lines_to_print(bool is_matching_line, int* p_lines_to_print, Regex_And_Flags* my_regex_and_flags)
{
    if (my_regex_and_flags->flags[A_FLAG] == false)
        return is_matching_line;
    
    else if (is_matching_line)
    {
        *p_lines_to_print = my_regex_and_flags->A_flag_value;
        return true;
    }
    else if (*p_lines_to_print > 0)
    {
        (*p_lines_to_print) -= 1;
        return true;
    }
    else return false;
}

bool check_if_matching_line(Line_Descriptor* line_desc, Regex_And_Flags* my_regex_and_flags)
{
    char* line = line_desc->line;
    bool is_matching = false;
    size_t i;

    for (i = 0; i < strlen(line_desc->line); i++) 
    {
        if (check_x_flag_and_start_of_line(my_regex_and_flags->flags[X_FLAG], i))
            return false;

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
    {
        if (check_x_flag_and_end_of_line(flags[X_FLAG], *line))
            return false;

        return true;
    }

    if (*line == '\0'|| *line == '\n')
        return false;

    switch (regex_blocks->type)
    {
    case REGEX_TYPE_DOT:
        return is_matching_expression_at_place(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

    case REGEX_TYPE_REGULAR_CHAR:
        if (compare_chars(*line, regex_blocks->regex_block_contents.regular_char, flags[I_FLAG]) == false)
            return false;
        return is_matching_expression_at_place(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

    case REGEX_TYPE_BRACKETS:
        if (check_if_char_in_range(*line, regex_blocks->regex_block_contents.bracket_block) == false)
            return false;
        return is_matching_expression_at_place(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

    case REGEX_TYPE_PARENTHESES:
        return check_if_parentheses_and_rest_of_line_match(line, regex_blocks, regex_block_num, flags);
    }
    return false;
}

bool check_if_parentheses_and_rest_of_line_match(char* line, Regex_Block* regex_blocks, int regex_block_num, bool* flags)
{ 
    bool is_left_side_matching = false, is_right_side_matching = false; 

    Regex_Block_Contents* block_contents = &(regex_blocks->regex_block_contents);

    char* left_side = block_contents->parentheses_block.left_side;
    char* right_side = block_contents->parentheses_block.right_side;

    if (check_if_line_starting_with_substring(line, right_side, flags[I_FLAG]))
        is_left_side_matching =  is_matching_expression_at_place(line + strlen(right_side), regex_blocks + 1,
                                                                 regex_block_num - 1, flags);
        
    if (check_if_line_starting_with_substring(line, left_side, flags[I_FLAG]))
        is_right_side_matching =  is_matching_expression_at_place(line + strlen(left_side), regex_blocks + 1,
                                                                  regex_block_num - 1, flags);
   
    return is_left_side_matching || is_right_side_matching;  
}

bool check_x_flag_and_start_of_line(bool x_flag, int line_index) 
{
    return (x_flag && line_index > 0);
}

bool check_x_flag_and_end_of_line(bool x_flag, char current_char)
{
    return (x_flag && (current_char != '\0' && current_char != '\n'));
}

void grep_printer(Line_Descriptor* line_desc, bool is_matching, bool* flags, bool is_first_matching_block)
{
    if (flags[C_FLAG])
        return;

    char separator = is_matching ? MATCHING_LINE_SEPARATOR : 
                                   NOT_MATCHING_LINE_SEPARATOR;

    print_lines_block_separator_if_new_block(is_matching, flags, is_first_matching_block);

    if (flags[B_FLAG])
        printf("%ld%c%s", line_desc->byte_counter - strlen(line_desc->line), separator, line_desc->line);

    else if (flags[N_FLAG])
        printf("%d%c%s", line_desc->line_counter, separator, line_desc->line);

    else 
        printf("%s", line_desc->line);
}

void print_lines_block_separator_if_new_block(bool is_matching, bool* flags, bool is_first_matching_block)
{

    if (is_matching)
    {
        if (flags[A_FLAG] && flags[N_FLAG] == false && flags[B_FLAG] == false && (is_first_matching_block == false))
            printf("%s\n", LINES_BLOCK_SEPARATOR);
    }
}

void handle_c_flag(bool c_flag, int matching_lines_amount) 
{
    if (c_flag)
        printf("%d\n", matching_lines_amount);
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

bool check_if_line_starting_with_substring(const char* line, const char* substring, bool is_case_insensitive)
{
    while(*line !='\0'  && *substring != '\0')
    {
        if(compare_chars(*line, *substring, is_case_insensitive) == false)
            return false;
        line++;
        substring++;
    }

    if (*substring == '\0')
        return true;

    return false;
}

bool compare_chars(const char first_char, const char second_char, bool is_case_insensitive)
{
  if (is_case_insensitive)
    return (tolower(first_char) == tolower(second_char));

  return (first_char == second_char);
}

bool check_if_char_in_range(char current_char, Bracket bracket_block)
{
    return (current_char >= bracket_block.bracket_start && 
            current_char <= bracket_block.bracket_end);
}
