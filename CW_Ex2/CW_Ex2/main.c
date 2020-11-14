#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "regex_handler.h"
#include "common.h"
#include "cmd_parser.h"

void print_expression_and_flags(ExpressionAndFlags* expression_and_flags); 
void free_main_resources(const char* msg, const char* file, int line, const char* func_name, 
						 LineDescriptor* line_desc, ExpressionAndFlags* pattern_and_flags  ); 


int main(int argc, char* argv[])
{
	int return_code;

	if (argc < 2)
	{
		print_error(MSG_ERR_NUM_ARGS, __FILE__, __LINE__, __func__);
		return RETURN_CODE_ERROR;
	}

	FILE* f_input;
	char* file_name = NULL;
	ExpressionAndFlags* expression_and_flags;

	return_code = parse_cmd_args(argc, argv, &expression_and_flags, &file_name);

	if (return_code == RETURN_CODE_ERROR)
		return RETURN_CODE_ERROR;

	if (file_name == NULL)
		f_input = stdin;
	else
	{
		f_input = fopen(file_name, "w");

		if (f_input == NULL)
		{
			print_error(MSG_ERR_CANNOT_OPEN_FILE, __FILE__, __LINE__, __func__);
			return RETURN_CODE_ERROR;
		}
	}

	// iterate over file - main 
	// find matching line - regex_handler, line descriptor handler 
	// print              - logger



	print_expression_and_flags(expression_and_flags);



	fclose(f_input); 
	return 0;
}

void print_expression_and_flags(ExpressionAndFlags* expression_and_flags)
{

	printf("expression = %s\n", expression_and_flags->expression);
	flag j;
	printf("A_flag_value = %d\n", expression_and_flags->A_flag_value);
	for (j = FLAGS_START; j < FLAGS_END; j++)
	{
		printf("%s = %d \n", FLAGS_STR_ARRAY[j], expression_and_flags->flags[j]);
	}
}

void free_main_resources(const char* msg, const char* file, int line, const char* func_name ,
					LineDescriptor* line_desc, ExpressionAndFlags* pattern_and_flags) 
{
	print_error(msg, file, line, func_name);

	if (line_desc != NULL)
		free(line_desc);

	if (pattern_and_flags != NULL)
		free(pattern_and_flags);

}


