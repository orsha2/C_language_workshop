#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "my_grep.h" 

typedef struct _Line_Descriptor {
	char* line;
	int   line_counter;
	int   byte_counter;
} Line_Descriptor;


void print_expression_and_flags(Regex_And_Flags* expression_and_flags, char* expression);
void print_regex(Regex_And_Flags* my_regex_and_flags);
void init_line(Line_Descriptor* line_desc, char* line_buffer);
bool check_if_matching_line(Line_Descriptor* line_desc, Regex_And_Flags* my_regex_and_flags);
bool is_matching_expression(char* line, Regex_Block* regex_blocks,  int regex_block_num, bool* flags);
void print_if_matching(Line_Descriptor* line_desc, bool is_matching, bool* flags); 
char* to_lowercase(char* line); 

Error_Code_t grep_execute_on_stream(FILE* input_stream, Regex_And_Flags* my_regex_and_flags)
{	

	Line_Descriptor line_desc = { NULL, 0, 0 };

	//-----------------------------
	char* line = (char*)malloc(500 * sizeof(char)); 
	void* status = fgets(line ,input_stream, input_stream); // getline
	//-----------------------------

	bool is_matching_line;

	while (status != NULL)
	{

		init_line(&line_desc, line);

		is_matching_line = check_if_matching_line (&line_desc , my_regex_and_flags);
		print_if_matching(&line_desc, is_matching_line, my_regex_and_flags->flags);

		//printf("line: %s", line_buffer);

		//-----------------------------
		status = fgets(line, input_stream, input_stream); // getline
		//-----------------------------

	}
	return SUCCESS_CODE; 
}


bool check_if_matching_line (Line_Descriptor* line_desc, Regex_And_Flags* my_regex_and_flags)
{
	char* line = line_desc->line; 
	bool is_matching = false;
	for (int i = 0; i < strlen(line_desc->line); i++)
	{
		is_matching = is_matching_expression(line + i, my_regex_and_flags->regex_array,
			my_regex_and_flags->regex_array_len, my_regex_and_flags->flags);
	
		if (is_matching)
			break; 
	}

	if (my_regex_and_flags->flags[V_FLAG])
		return (!is_matching); 

	return is_matching;
}

bool is_matching_expression(char* line, Regex_Block* regex_blocks, int regex_block_num, bool* flags)
{
	//printf("%s\n", line);
	if (regex_block_num == 0)
		return true;
	if (*line == '\0')
		return false;

	switch (regex_blocks->type)
	{
	case REGEX_TYPE_DOT:
		return is_matching_expression(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

	case REGEX_TYPE_REGULAR_CHAR:
		if (*line != regex_blocks->regex_block_contents.regular_char)
			return false;
		return is_matching_expression(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

	case REGEX_TYPE_PARENTHESES:
		// TODO
		break;

	case REGEX_TYPE_BRACKETS:
		// TODO
		break;

	}
	return true;
}

void print_if_matching(Line_Descriptor* line_desc, bool is_matching, bool* flags)
{
	if (is_matching == false)
		return;

	if (flags[B_FLAG])
		printf("%d: %s", line_desc->byte_counter - strlen(line_desc->line), line_desc->line);

	else if (flags[N_FLAG])
		printf("%d: %s", line_desc->line_counter, line_desc->line);

	else if (flags[C_FLAG])
		printf("%d", line_desc->line_counter);

	else printf("%s", line_desc->line);
}



void init_line(Line_Descriptor* line_desc, char* line_buffer)
{
	int line_counter = 0;
	int bytes_counter = 0;

	//char* line = getline();

	line_counter = line_desc->line_counter + 1;
	bytes_counter = line_desc->byte_counter + strlen(line_buffer);

	line_desc->line = line_buffer;
	line_desc->line_counter = line_counter;
	line_desc->byte_counter = bytes_counter;

	//return return_code; 
}

/*
char* to_lowercase(char* line)
{
	char* p_start = line;
	while (*line != '\0')
	{
		*line = tolower(*line);
		line++;
	}
	return p_start;
}

bool compare_chars(const char first_char, const char second_char, bool is_case_sensitive) 
{
	if (is_case_sensitive)
		return (first_char == second_char);

	return (tolower(first_char) == tolower(second_char));
}

bool compare_strings(const char* first_str, const char* second_str, bool is_case_sensitive)
{
	if (is_case_sensitive)
		return (first_char == second_char);

	return (tolower(first_char) == tolower(second_char));
	
	while (*first_str != '\0' && *second_str != '\0')
	{
		if (is_case_sensitive)
			if (*first_str != *second_str)
				return false;

		first_str++;
		second_str++;
	}

	if (*first_str != '\0' || *second_str != '\0')
		return false;

	return true;
}

Error_Code_t read_line_from_stream(FILE** input_stream, char* line_buffer, int line_len)
{
	if (line_buffer == NULL)
		line_buffer = (char*)malloc(line_len * sizeof(char));

	if (line_buffer == NULL)
	{
		print_error(MSG_ERR_MEM_ALLOC, __FILE__, __LINE__, __func__);
		return MEM_ALLOC_ERROR;
	}
	line_buffer = fgets(line_buffer, line_len, *input_stream);
	return SUCCESS_CODE;

}*/



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ helpers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
void print_expression_and_flags(Regex_And_Flags* my_regex_and_flags, char* expression)
{

	printf("expression = %s\n", expression);
	Flag j;
	printf("A_flag_value = %d\n", my_regex_and_flags->A_flag_value);
	for (j = FLAGS_START; j < FLAGS_END; j++)
	{
		printf("%s = %d \n", FLAGS_STR_ARRAY[j], my_regex_and_flags->flags[j]);
	}
}

void print_regex(Regex_And_Flags* my_regex_and_flags)
{

	Regex_Block* reg_array = my_regex_and_flags->regex_array;
	int len = my_regex_and_flags->regex_array_len;

	for (int j = 0; j < len; j++)
	{
		switch (reg_array[j].type)
		{
		case REGEX_TYPE_DOT:
			printf(".");
			break;

		case REGEX_TYPE_REGULAR_CHAR:
			printf("%c", (reg_array + j)->regex_block_contents.regular_char);
			break;

		case REGEX_TYPE_PARENTHESES:
			printf("(%s|%s)", (reg_array + j)->regex_block_contents.parentheses_block.left_side,
				(reg_array + j)->regex_block_contents.parentheses_block.right_side);
			break;
		case REGEX_TYPE_BRACKETS:
			printf("[%c-%c]", (reg_array + j)->regex_block_contents.bracket_block.bracket_start,
				(reg_array + j)->regex_block_contents.bracket_block.bracket_end);
			break;
		}
	}
	printf("\n");
}