
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "regex_handler.h"
#include "common.h"

int parse_cmd_args(int arg_num, const char** args, LineDescriptor** p_line_desc, ExpressionAndFlags** expression_and_flags, FILE* f_input);
void initialze_expression(const char* arg, ExpressionAndFlags* expression_and_flags);
void initialze_flags(ExpressionAndFlags* expression_and_flags);
int load_flag_and_update_index(const char** args, int i, ExpressionAndFlags* expression_and_flags);
int get_flag_index(const char* current_flag);
void free_main_resources(const char* msg, const char* file, int line, const char* func_name,LineDescriptor* line_desc, ExpressionAndFlags* pattern_and_flags);




int main(int argc, char* argv[])
{
	int return_code;

	if (argc < 2)
	{
		print_error(MSG_ERR_NUM_ARGS, __FILE__, __LINE__, __func__);
		return RETURN_CODE_ERROR;
	}

	LineDescriptor* line_desc;
	ExpressionAndFlags* flags;
	FILE* f_input; 

	return_code = parse_cmd_args(argc, argv, &line_desc, &flags , &f_input);

	if (return_code == RETURN_CODE_ERROR)
		return RETURN_CODE_ERROR;


	return 0;
}

int parse_cmd_args(int arg_num, const char** args, LineDescriptor** p_line_desc, ExpressionAndFlags** p_expression_and_flags, FILE** f_input)
{
	int i;
	char* arg, file_name;

	(*p_line_desc) = (LineDescriptor*)malloc(sizeof(LineDescriptor));
	(*p_expression_and_flags) = (ExpressionAndFlags*)malloc(sizeof(ExpressionAndFlags));
	f_input = stdin;

	if (*p_line_desc == NULL || *p_expression_and_flags == NULL)
		free_main_resources(MSG_ERR_MEM_ALLOC, __FILE__, __LINE__, __func__, *p_line_desc, *p_expression_and_flags, NULL);

	initialze_flags(*p_expression_and_flags);

	i = 1;
	int index;
	while (i < arg_num)
	{
		index = load_flag_and_update_index(args, i, *p_expression_and_flags);

		if (index == NOT_A_FLAG)
			break;

		i = index;
	
	}


	initialze_expression(args[i], p_expression_and_flags);

	printf("%s\n", (*p_expression_and_flags)->expression);
	exit(0);

	//~~~~~~~~~~~~~~~~



	printf("%s\n", (*p_expression_and_flags)->expression);
	
	flag j;
	printf("%d", (*p_expression_and_flags)->a_flag_value);
	for (j = FLAGS_START; j < FLAGS_END; j++)
	{
		printf("%d field =  %d, ",j, (*p_expression_and_flags)->flags[j]);
	}
	//~~~~~~~~~~~~~~~~

	i++;

	if (i <= arg_num - 1)
	{
		file_name = args[i];
		f_input = fopen(file_name, "r");

		if (f_input == NULL) 
		{
			free_main_resources(MSG_ERR_CANNOT_OPEN_FILE ,__FILE__ ,  __LINE__,  __func__ , *p_line_desc, *p_expression_and_flags, NULL);
			return RETURN_CODE_ERROR;
		}


		//printf("%s\n", file_name);
	}

	//~~~~~~~~~~~~~~~~
	//printf("%s\n", file_name);
	printf("%s\n", (*p_expression_and_flags)->expression);

	printf("%d", (*p_expression_and_flags)->a_flag_value);
	for (j = FLAGS_START; j < FLAGS_END; j++)
	{
		printf("%d field =  %d, ",j, (*p_expression_and_flags)->flags[j]);
	}

	// -i -b -c abc in.txt
	//~~~~~~~~~~~~~~~~ 
	
	return RETURN_CODE_VALID;

}

void initialze_expression( const char* arg, ExpressionAndFlags* expression_and_flags)
{
	
	strcpy(expression_and_flags->expression, arg);

}

void initialze_flags(ExpressionAndFlags* expression_and_flags)
{
	flag current_flag;

	for (current_flag = FLAGS_START; current_flag < FLAGS_END; current_flag++)
	{
		expression_and_flags->flags[current_flag] = false;
	}
}

int load_flag_and_update_index(const char** args, int i, ExpressionAndFlags* expression_and_flags)
{

	flag current_flag = get_flag_index(args[i]);

	if (current_flag == NOT_A_FLAG)
		return NOT_A_FLAG;

	expression_and_flags->flags[current_flag] = true;

	if (current_flag == A_FLAG)
	{
		expression_and_flags->a_flag_value = atoi(args[i + 1]);
		i++;
	}

	i++;
	return i;
}

int get_flag_index(const char* current_flag)
{
	flag i;
	for (i = FLAGS_START; i < FLAGS_END; i++)
	{
		if (strcmp(current_flag, FLAGS_STR_ARRAY[i]) == 0)
			return i;
	}

	return NOT_A_FLAG;
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


