#include <stdio.h>
#include <string.h>
#include "regex_handler.h"
#include "common.h"

void initialze_flags(ExpressionAndFlags* expression_and_flags); 
int load_flag_and_update_index( char** args, int i, ExpressionAndFlags* expression_and_flags);
void load_expression(char* arg, ExpressionAndFlags* expression_and_flags);
int get_flag_index(const char* current_flag);


int parse_cmd_args(int arg_num, char** args, ExpressionAndFlags** p_expression_and_flags, char** p_file_name)
{
	int arg_index, expression_index;

	(*p_expression_and_flags) = (ExpressionAndFlags*)malloc(sizeof(ExpressionAndFlags));

	if (*p_expression_and_flags == NULL)
	{
		print_error(MSG_ERR_MEM_ALLOC, __FILE__, __LINE__, __func__);
		return RETURN_CODE_ERROR; 
	}

	initialze_flags(*p_expression_and_flags);

	arg_index = 1, expression_index = 1;
	while (arg_index < arg_num)
	{
		arg_index = load_flag_and_update_index(args, arg_index, *p_expression_and_flags);

		if (arg_index == NOT_A_FLAG)
			break;

		expression_index = arg_index;
	}

	load_expression(args[expression_index], *p_expression_and_flags);
	
	arg_index++;
	
	if (arg_index <= arg_num - 1)
		*p_file_name = args[arg_index];
	
	return RETURN_CODE_VALID;
}

void load_expression(char* arg, ExpressionAndFlags* expression_and_flags)
{
	expression_and_flags->expression = arg;

}

void initialze_flags(ExpressionAndFlags* expression_and_flags)
{
	flag current_flag;

	for (current_flag = FLAGS_START; current_flag < FLAGS_END; current_flag++)
	{
		expression_and_flags->flags[current_flag] = false;
	}
}

int load_flag_and_update_index( char** args, int i, ExpressionAndFlags* expression_and_flags)
{
	flag current_flag = get_flag_index(args[i]);

	if (current_flag == NOT_A_FLAG)
		return NOT_A_FLAG;

	expression_and_flags->flags[current_flag] = true;

	if (current_flag == A_FLAG)
	{
		expression_and_flags->A_flag_value = atoi(args[i + 1]);
		i++;
	}

	i++;
	return i;
}

int get_flag_index(const char* current_flag)
{
	flag index;
	for (index = FLAGS_START; index < FLAGS_END; index++)
	{
		if (strcmp(current_flag, FLAGS_STR_ARRAY[index]) == 0)
			return index;
	}

	return NOT_A_FLAG;
}

