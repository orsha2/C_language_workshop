#include <stdio.h>
#include <string.h>
#include "regex_handler.h"
#include "error_mgr.h"

typedef enum _char_type {
	CHAR_DOT,
	CHAR_REGULAR,
	CHAR_BRACKETS_START,
	CHAR_BRACKETS_END, 
	CHAR_BACK_SLASH
}char_type;

const char* FLAGS_STR_ARRAY[] = { "-i", "-v", "-c", "-n", "-x", "-b", "-E", "-A" };


regex* initialize_regex_array(char* expression);
char_type classify_char_type(char my_char);
int count_amount_of_regex_blocks(char* expression);
int get_bracket_block_end(char* expression, int index); 


error_code_t initialize_regex_array(char* expression, regex** p_regex_array, int* p_regex_array_len)
{
	 int index;
	 *p_regex_array_len = count_amount_of_regex_blocks(expression);
	 *p_regex_array = (regex*)malloc(sizeof(regex) * (*p_regex_array_len));

	 if (*p_regex_array != NULL)
	 {
		 print_error(MSG_ERR_MEM_ALLOC, __FILE__, __LINE__, __func__);
		 return MEM_ALLOC_ERROR;
	 }
	
	
	char* rest_of_expression = expression;
	for (index = 0 ; index < (*p_regex_array_len); index++)
		rest_of_expression = init_regex_block_and_advance_expression(&p_regex_array[index], rest_of_expression);
	
	return SUCCESS_CODE;
}

// ---------------------------------------------------------------------------- CHECK IF WORKS 
char* init_regex_block(regex* current_regex, char* rest_of_expression)
{
	char_type current_char_type;

	current_char_type = classify_char_type(*rest_of_expression);

	switch (current_char_type)
	{
	case CHAR_DOT:
		current_regex->type = TYPE_DOT;
		break;

	case CHAR_REGULAR:
		current_regex->type = TYPE_REGULAR_CHAR;
		current_regex->regex_block.regular_char = rest_of_expression[0];
		break;

	case CHAR_BACK_SLASH:
		current_regex->type = TYPE_REGULAR_CHAR;
		current_regex->regex_block.regular_char = rest_of_expression[1];
		rest_of_expression++;
		break;
	//----------------
	case CHAR_BRACKETS_START:
		index = get_bracket_block_end(index, *rest_of_expression, rest_of_expression);
		break;
	//----------------
	}

	return rest_of_expression;
}

int count_amount_of_regex_blocks(char* expression)
{
	int block_counter = 0, index = 0;
	char current_char; 
	char_type current_char_type;

	while (index < strlen(expression))
	{
		current_char = expression[index];
		current_char_type = classify_char_type(current_char);

		switch (current_char_type)
		{
		case CHAR_REGULAR_CHAR:
		case CHAR_DOT:
			block_counter++;
			break;

		case CHAR_BACK_SLASH:
			block_counter++;
			index++;
			break;

		case CHAR_BRACKETS_START:
			block_counter++;
			index = get_bracket_block_end(index, current_char, expression);
			break;

		}
	}
	return block_counter; 
}


int get_bracket_block_end(char* expression, int index)
{
	char current_char;
	char_type current_char_type;
	do
	{
		current_char = expression[index];
		current_char_type = classify_char_type(current_char);
		index++;
		
	} while (current_char_type != BRACKETS_END);

	return index;
}

char_type classify_char_type(char my_char) 
{
	if (my_char == '(' || my_char == '[')
		return CHAR_BRACKETS_START;

	if (my_char == ')' || my_char == ']')
		return CHAR_BRACKETS_END;

	if (my_char == '\\')
		return CHAR_BACK_SLASH;

	if (my_char == '.')
		CHAR_DOT;

	return CHAR_REGULAR;


}