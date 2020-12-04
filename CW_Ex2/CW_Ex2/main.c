#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "cmd_parser.h"
#include "error_mgr.h"
#include "init_regex.h"
#include "my_grep.h"

#define MIN_ARGS_NUM 2
#define MAX_ARGS_NUM 12

Error_Code_t initialize_input_stream(char* file_name, FILE** p_f_input);
void free_main_resources(FILE* input_stream, Regex_And_Flags* pattern_and_flags);
Error_Code_t assert_argc_value_range(int argc);
void free_paretheses_block(Parentheses* parentheses_block);

int main(int argc, char* argv[])
{
    Error_Code_t status;

    FILE* input_stream = NULL;
    char* file_name = NULL;
    char* expression;
    Regex_And_Flags* my_regex_and_flags = NULL;

    status = assert_argc_value_range(argc);
    
    if (status != SUCCESS_CODE)
        goto main_exit;

    status = parse_cmd_args(argc, argv, &my_regex_and_flags, &expression, &file_name);

    if (status != SUCCESS_CODE)
        goto main_exit;

    status = initialize_regex_array(expression, &my_regex_and_flags->regex_array, &(my_regex_and_flags->regex_array_len),
        my_regex_and_flags->flags[E_FLAG]);

    if (status != SUCCESS_CODE)
        goto main_exit;

    status = initialize_input_stream(file_name, &input_stream);

    if (status != SUCCESS_CODE)
        goto main_exit;

    grep_execute_on_stream(input_stream, my_regex_and_flags);

main_exit:
    free_main_resources(input_stream, my_regex_and_flags);

    return (int)status;
}

Error_Code_t initialize_input_stream(char* file_name, FILE** p_f_input)
{
    if (file_name == NULL)
        *p_f_input = stdin;

    else 
    {
        *p_f_input = fopen(file_name, "r");

        if (*p_f_input == NULL)
        {
            print_error(MSG_ERR_CANNOT_OPEN_FILE, __FILE__, __LINE__, __func__);
            return FILE_OPEN_FAILED;
        }
    }
    return SUCCESS_CODE;
}

void free_main_resources(FILE* input_stream, Regex_And_Flags* my_regex_and_flags)
{
    if (input_stream != NULL)
        fclose(input_stream);

    if (my_regex_and_flags == NULL)
        return;

    Regex_Block* regex_array = my_regex_and_flags->regex_array;
    int i;
    for (i = 0; i < my_regex_and_flags->regex_array_len; i++) {
        if (regex_array->type != REGEX_TYPE_PARENTHESES)
            continue;

        free_paretheses_block(&(regex_array->regex_block_contents.parentheses_block));
    }

    free(regex_array);
    free(my_regex_and_flags);
}

void free_paretheses_block(Parentheses* parentheses_block)
{
    char* parenthesis_contents = parentheses_block->left_side;

    if (parenthesis_contents != NULL)
        free(parenthesis_contents);
}

Error_Code_t assert_argc_value_range(int argc)
{
    if (argc >= MIN_ARGS_NUM && argc <= MAX_ARGS_NUM)
        return SUCCESS_CODE;

    print_error(MSG_ERR_NUM_ARGS, __FILE__, __LINE__, __func__);
    return ARGS_NUM_ERROR;
}