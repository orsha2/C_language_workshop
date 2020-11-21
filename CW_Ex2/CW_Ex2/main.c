#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "regex_handler.h"
#include "error_mgr.h"
#include "cmd_parser.h"

void print_expression_and_flags(regex_and_flags* expression_and_flags, char* expression); 
void free_main_resources(const char* msg, const char* file, int line, const char* func_name, 
						 line_descriptor* line_desc, regex_and_flags* pattern_and_flags  ); 

void init_line(FILE* f_input, line_descriptor* line_desc);

int main(int argc, char* argv[])
{
	error_code_t status;

	FILE* f_input = NULL;
	char* file_name = NULL;
	char* expression;
	regex_and_flags* my_regex_and_flags;
	char line_buffer[500]; // <------------------------------------------------------------------------ Change this to support getline

	if (argc < 2)
	{
		print_error(MSG_ERR_NUM_ARGS, __FILE__, __LINE__, __func__);
		status = ARGS_NUM_ERROR;
		goto main_exit;
	}

	status = parse_cmd_args(argc, argv, &my_regex_and_flags, &expression, &file_name);

	if (status != SUCCESS_CODE)
		goto main_exit; 

	status = initialize_regex(expression, 
		&(my_regex_and_flags->regex_array), &(my_regex_and_flags->regex_array_len));

	if (status != SUCCESS_CODE)
		goto main_exit;
	//print_expression_and_flags(expression_and_flags);
	
	status = initialize_input_stream(file_name, &f_input); 

	if (status != SUCCESS_CODE)
		goto main_exit;

	//printf("%d\n", f_input);

	line_descriptor line_desc = {NULL, 0, 0};

	int scan_status = fscanf(f_input, " %[^\n]", line_buffer);

	while (scan_status != EOF)
	{
		init_line(&line_desc, line_buffer);
		// printf("%s %d %d \n", line_desc.line, line_desc.line_counter, line_desc.byte_counter);
		
		// regex 
		
		scan_status = fscanf(f_input, " %[^\n]", line_buffer);
	}


main_exit:
	if (f_input != NULL)
		fclose(f_input);

	//free_main_resources();

	return status;
}


void init_line(line_descriptor* line_desc, char* line_buffer)
{
	int return_code;
	int line_counter = 0;
	int bytes_counter = 0;
	
	//char* line = getline();


	line_counter =  line_desc->line_counter + 1;
	bytes_counter = line_desc->byte_counter + strlen(line_buffer);

	line_desc->line = line_buffer;
	line_desc->line_counter = line_counter;
	line_desc->byte_counter = bytes_counter;

	//return return_code; 
}


error_code_t initialize_input_stream(char* file_name, FILE** p_f_input)
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

void print_expression_and_flags(regex_and_flags* my_regex_and_flags, char* expression)
{

	printf("expression = %s\n", expression);
	flag j;
	printf("A_flag_value = %d\n", my_regex_and_flags->A_flag_value);
	for (j = FLAGS_START; j < FLAGS_END; j++)
	{
		printf("%s = %d \n", FLAGS_STR_ARRAY[j], my_regex_and_flags->flags[j]);
	}
}

void free_main_resources(const char* msg, const char* file, int line, const char* func_name,
					line_descriptor* line_desc, regex_and_flags* pattern_and_flags) 
{
	print_error(msg, file, line, func_name);

	if (line_desc != NULL)
		free(line_desc);

	if (pattern_and_flags != NULL)
		free(pattern_and_flags);

}


