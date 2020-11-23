#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regex_handler.h"
#include "error_mgr.h"

#define FIRST_CHAR_IN_STR  0 
#define SECOND_CHAR_IN_STR 1 

typedef enum _Char_Type {
	CHAR_REGULAR,
	CHAR_DOT,
	CHAR_PARENTHESES_START,
	CHAR_PARENTHESES_END,
	CHAR_BRACKETS_START,
	CHAR_BRACKETS_END, 
	CHAR_BACK_SLASH,
	CHAR_APOSTROPHE
}Char_Type;

const char* FLAGS_STR_ARRAY[] = { "-i", "-v", "-c", "-n", "-x", "-b", "-E", "-A" };

Error_Code_t init_regex_block_and_advance_expression(Regex_Block* current_regex_block, char** p_rest_of_expression);
int get_bracket_block_end(char* expression, int index);
Error_Code_t set_parentheses_block_return_status(char* parentheses_block_start, Regex_Block* current_regex_block);
void set_parentheses_block_contents(Regex_Block_Contents* regex_block_contents, char* left_side, char* right_side);
char* set_bracket_block(char* bracket_block_start, Regex_Block* current_regex_block);
void set_regular_char_block(char regular_char, Regex_Block* current_regex_block);

void strcpy_until_char(char** p_dest, const char** p_source, char end_char);
int get_bracket_block_end(char* expression, int index);
int count_amount_of_regex_blocks(char* expression);
Char_Type classify_char_type(char my_char);


Error_Code_t initialize_regex_array(char* expression, Regex_Block** p_regex_array, int* p_regex_array_len, bool is_E_flag)
{
	Error_Code_t status = SUCCESS_CODE;
	int index;
	*p_regex_array_len = count_amount_of_regex_blocks(expression);
	*p_regex_array = (Regex_Block*)malloc(sizeof(Regex_Block) * (*p_regex_array_len));
	Regex_Block* regex_array = *p_regex_array;

	if (regex_array == NULL)
	{
		print_error(MSG_ERR_MEM_ALLOC, __FILE__, __LINE__, __func__);
		return MEM_ALLOC_ERROR;
	}

	// ------------------------------------------------------------------------ 
	// add ignore '\'' func ?
	char* rest_of_expression = is_E_flag ? (expression + 1) : expression;
	// ------------------------------------------------------------------------

	for (index = 0; index < (*p_regex_array_len); index++) 
	{
		status = init_regex_block_and_advance_expression(&(regex_array[index]), &rest_of_expression);

		if (status != SUCCESS_CODE)
			break;
	}

	return status;
}


Error_Code_t init_regex_block_and_advance_expression(Regex_Block* current_regex_block, char** p_rest_of_expression)
{
	char* rest_of_expression = *p_rest_of_expression;
	Char_Type current_char_type;
	int index;
	current_char_type = classify_char_type(*rest_of_expression);
	Error_Code_t status = SUCCESS_CODE;

	switch (current_char_type)
	{
	case CHAR_DOT:
		current_regex_block->type = REGEX_TYPE_DOT;
		break;

	case CHAR_REGULAR:
		set_regular_char_block(rest_of_expression[FIRST_CHAR_IN_STR], current_regex_block);
		break;

	case CHAR_BACK_SLASH:
		set_regular_char_block(rest_of_expression[SECOND_CHAR_IN_STR], current_regex_block);
		rest_of_expression++;
		break;

	case CHAR_PARENTHESES_START: 
		rest_of_expression++;
		status = set_parentheses_block_return_status(&rest_of_expression, current_regex_block);
		break;

	case CHAR_BRACKETS_START:
		rest_of_expression = set_bracket_block(rest_of_expression, current_regex_block);
		break;
	}

	rest_of_expression++;
	*p_rest_of_expression = rest_of_expression;

	return status;
}

void set_regular_char_block(char regular_char , Regex_Block* current_regex_block)
{
	current_regex_block->type = REGEX_TYPE_REGULAR_CHAR;
	current_regex_block->regex_block_contents.regular_char = regular_char;
}

Error_Code_t set_parentheses_block_return_status(char** p_parentheses_block_start, Regex_Block* current_regex_block)
{
	char* left_side;
	char* right_side;
	current_regex_block->type = REGEX_TYPE_PARENTHESES;

	int size_of_block = get_bracket_block_end(*p_parentheses_block_start, FIRST_CHAR_IN_STR);

	char* parentheses_contents = (char*)malloc((size_of_block) * sizeof(char));
	if (parentheses_contents == NULL)
	{
		 print_error(MSG_ERR_MEM_ALLOC, __FILE__, __LINE__, __func__);
		 return MEM_ALLOC_ERROR;
	}

	left_side = parentheses_contents;
	strcpy_until_char(&parentheses_contents, p_parentheses_block_start, '|');

	(*p_parentheses_block_start)++;
	right_side = parentheses_contents;
	strcpy_until_char(&parentheses_contents, p_parentheses_block_start, ')');

	set_parentheses_block_contents(&current_regex_block->regex_block_contents, left_side, right_side );
	
	return SUCCESS_CODE;
}

void strcpy_until_char(char** p_dest , const char** p_source, char end_char)
{ 

	while (**p_source != end_char && **p_source != '\0')
	{
		(**p_dest) = (**p_source);
		(*p_source)++;
		(*p_dest)++;
	}
	(**p_dest) = '\0';
	(*p_dest)++;
}

void set_parentheses_block_contents(Regex_Block_Contents* regex_block_contents, char* left_side, char* right_side)
{
	regex_block_contents->parentheses_block.left_side = left_side;
	regex_block_contents->parentheses_block.right_side = right_side;
}

char* set_bracket_block(char* bracket_block_start, Regex_Block* current_regex_block)
{
	int bracket_end_index = get_bracket_block_end(bracket_block_start, FIRST_CHAR_IN_STR); 

	current_regex_block->type = REGEX_TYPE_BRACKETS;
	current_regex_block->regex_block_contents.bracket_block.bracket_start = bracket_block_start[SECOND_CHAR_IN_STR];
	current_regex_block->regex_block_contents.bracket_block.bracket_end = bracket_block_start[bracket_end_index-1];

	bracket_block_start += bracket_end_index; 

	return bracket_block_start;
}


int count_amount_of_regex_blocks(char* expression)
{
	int block_counter = 0, current_char_index = 0;
	char current_char; 
	Char_Type current_char_type;

	while (current_char_index < strlen(expression))
	{
		current_char = expression[current_char_index];
		current_char_type = classify_char_type(current_char);

		switch (current_char_type)
		{
		case CHAR_BACK_SLASH:
			block_counter++;
			current_char_index++;
			break;

		case CHAR_REGULAR:
		case CHAR_DOT:
			block_counter++;
			break;

		case CHAR_PARENTHESES_START:
		case CHAR_BRACKETS_START:
			block_counter++;
			current_char_index = get_bracket_block_end(expression, current_char_index);
			break;
		}
		current_char_index++;
	}

	return block_counter; 
}


int get_bracket_block_end(char* expression, int index)
{
	char current_char;
	Char_Type current_char_type;
	do
	{
		
		current_char = expression[index];
		current_char_type = classify_char_type(current_char);
		index++;

	} while (current_char != '\0' &&
			 current_char_type != CHAR_PARENTHESES_END && 
			 current_char_type != CHAR_BRACKETS_END);
			 
	index--;
	return index;
}

//---------------------------------------------------------------------------
//	TODO: Maybe change each char to enum, i.e. CHAR_PARENTHESES_START = '('
//---------------------------------------------------------------------------

Char_Type classify_char_type(char my_char) 
{
	switch (my_char)
	{
	case '(':
		return CHAR_PARENTHESES_START;

	case '[':
		return CHAR_BRACKETS_START;

	case ')':
		return CHAR_PARENTHESES_END;

	case ']':
		return CHAR_BRACKETS_END;

	case '\\':
		return CHAR_BACK_SLASH;

	case '.':
		return CHAR_DOT;

	case '\'':
		return CHAR_APOSTROPHE;
	}

	return CHAR_REGULAR; 
}

