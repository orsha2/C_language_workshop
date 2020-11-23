#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "error_mgr.h"
#include "cmd_parser.h"
#include "regex_handler.h"
#include "my_grep.h"


Error_Code_t initialize_input_stream(char* file_name, FILE** p_f_input);
void free_main_resources(const char* msg, const char* file, int line, const char* func_name, Regex_And_Flags* pattern_and_flags);

int main(int argc, char* argv[])
{
	Error_Code_t status;

	FILE* f_input = NULL;
	char* file_name = NULL;
	char* expression;
	Regex_And_Flags* my_regex_and_flags;

	if (argc < 2)
	{
		print_error(MSG_ERR_NUM_ARGS, __FILE__, __LINE__, __func__);
		status = ARGS_NUM_ERROR;
		goto main_exit;
	}

	status = parse_cmd_args(argc, argv, &my_regex_and_flags, &expression, &file_name);

	if (status != SUCCESS_CODE)
		goto main_exit; 

	status = initialize_regex_array(expression, &my_regex_and_flags->regex_array, &(my_regex_and_flags->regex_array_len), my_regex_and_flags->flags[E_FLAG] );
	
	if (status != SUCCESS_CODE)
		goto main_exit;
	
	status = initialize_input_stream(file_name, &f_input); 

	if (status != SUCCESS_CODE)
		goto main_exit;

	//printf("%d\n", f_input);

	//printf("-------------------------------------\n");
	print_expression_and_flags(my_regex_and_flags, expression);
	//printf("-------------------------------------\n");
	//print_regex(my_regex_and_flags);

	grep_execute_on_stream(f_input, my_regex_and_flags); 

main_exit:
	if (f_input != NULL)
		fclose(f_input);

	//free_main_resources();

	return status;
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

void free_main_resources(const char* msg, const char* file, int line, const char* func_name,
					 Regex_And_Flags* pattern_and_flags) 
{
	print_error(msg, file, line, func_name);

	if (pattern_and_flags != NULL)
		free(pattern_and_flags);

}

