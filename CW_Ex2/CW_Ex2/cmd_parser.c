#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init_regex.h"
#include "error_mgr.h"

void initialze_flags(bool flags_array[]); 
Flag load_flag_and_update_index( char** args, int *index, Regex_And_Flags* expression_and_flags);
int get_flag_index(const char* current_flag);


Error_Code_t parse_cmd_args(int arg_num, char** args, Regex_And_Flags** p_regex_and_flags, char** p_expression, char** p_file_name)
{
	int arg_index;
	Flag current_flag;

	(*p_regex_and_flags) = (Regex_And_Flags*)malloc(sizeof(Regex_And_Flags));

	if (*p_regex_and_flags == NULL)
	{
		print_error(MSG_ERR_MEM_ALLOC, __FILE__, __LINE__, __func__);
		return MEM_ALLOC_ERROR;
	}

	initialze_flags((*p_regex_and_flags)->flags);

	arg_index = 1;
	while (arg_index < arg_num)
	{
		current_flag = load_flag_and_update_index(args, &arg_index, *p_regex_and_flags);

		if (current_flag == NOT_A_FLAG)
			break;
	}

	*p_expression = args[arg_index];

	arg_index++;

	if (arg_index <= arg_num - 1 )
		*p_file_name = args[arg_index];
	
	return SUCCESS_CODE;
}

void initialze_flags(bool flags_array[])
{
	Flag current_flag;

	for (current_flag = FLAGS_START; current_flag < FLAGS_END; current_flag++)
		flags_array[current_flag] = false;
	
}

Flag load_flag_and_update_index( char** args, int *index, Regex_And_Flags* expression_and_flags)
{
	Flag current_flag = get_flag_index(args[*index]);

	if (current_flag == NOT_A_FLAG)
		return NOT_A_FLAG;

	expression_and_flags->flags[current_flag] = true;

	if (current_flag == A_FLAG)
	{
		expression_and_flags->A_flag_value = atoi(args[*index + 1]);
		(*index)++;
	}

	(*index)++;
	return current_flag;
}

int get_flag_index(const char* current_flag)
{
	Flag index;
	for (index = FLAGS_START; index < FLAGS_END; index++)
	{
		if (strcmp(current_flag, FLAGS_STR_ARRAY[index]) == 0)
			return index;
	}

	return NOT_A_FLAG;
}

