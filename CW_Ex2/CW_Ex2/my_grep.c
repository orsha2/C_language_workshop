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
void update_line_descriptor(Line_Descriptor* line_desc, char* line_buffer);
bool check_if_matching_line(Line_Descriptor* line_desc, Regex_And_Flags* my_regex_and_flags);
bool is_matching_expression(char* line, Regex_Block* regex_blocks,  int regex_block_num, bool* flags);
void print_if_matching(Line_Descriptor* line_desc, bool is_matching, bool* flags); 
bool compare_chars(const char first_char, const char second_char, bool is_case_insensitive);
bool compare_strings(const char* first_str, const char* second_str, bool is_case_insensitive); 


Error_Code_t grep_execute_on_stream(FILE* input_stream, Regex_And_Flags* my_regex_and_flags)
{	
	Error_Code_t status = SUCCESS_CODE; 
	Line_Descriptor line_desc = { NULL, 0, 0 };

	//-----------------------------
	char* line = (char*)malloc(500 * sizeof(char)); 
	void* fgets_status = fgets(line ,input_stream, input_stream); // getline
	//-----------------------------

	bool is_matching_line;

	while (fgets_status != NULL)
	{
		update_line_descriptor(&line_desc, line);

		is_matching_line = check_if_matching_line (&line_desc , my_regex_and_flags);
		print_if_matching(&line_desc, is_matching_line, my_regex_and_flags->flags);

		//-----------------------------
		fgets_status = fgets(line, input_stream, input_stream); // getline
		//-----------------------------

	}
	return status;
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
	if (regex_block_num == 0)
		return true;

	if (*line == '\0')
		return false;

	switch (regex_blocks->type)
	{
	case REGEX_TYPE_DOT:
		return is_matching_expression(line + 1, regex_blocks + 1, regex_block_num - 1, flags);

	case REGEX_TYPE_REGULAR_CHAR:
		if (compare_chars(*line, regex_blocks->regex_block_contents.regular_char, flags[I_FLAG]) == false)
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
		printf("%d\n", line_desc->line_counter);

	else printf("%s", line_desc->line);
}



void update_line_descriptor(Line_Descriptor* line_desc, char* line_buffer)
{
	int line_counter = 0;
	int bytes_counter = 0;

	//char* line = getline();

	line_counter = line_desc->line_counter + 1;
	bytes_counter = line_desc->byte_counter + strlen(line_buffer);

	line_desc->line = line_buffer;
	line_desc->line_counter = line_counter;
	line_desc->byte_counter = bytes_counter;

}


bool compare_chars(const char first_char, const char second_char, bool is_case_insensitive) 
{
	if (is_case_insensitive)
		return (tolower(first_char) == tolower(second_char));

	return (first_char == second_char);
}

bool compare_strings(const char* first_str, const char* second_str, bool is_case_insensitive)
{
	if (is_case_insensitive)
		return (_stricmp(first_str, second_str) == 0); // CHANGE THIS TO strcasecmp 

	return (strcmp(first_str, second_str) == 0); 
	
}

/*
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



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ helpers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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




/*
bla
----------------
BLABb
erg erg
g reg erg reg
vgb
efv
blabfew
blala ge ger
		rth rth bla
BlA
blA
 regb
 befwb
 ----------------
 blabfew
blala ge ger
				rth rth bla

				rth rth bla
------------------
bli

bla



		blu


blgrgbla ?!#
53523905?!bla!-
------------------


3: bla
10: blgrgbla ?!#
11: 53523905?!bla!-
-----------------------
bli

bla



		blu


blgrgbla ?!#
53523905?!bla!-

BLA
B12la bLa
BLU bLA


-------------------------
3: bla
10: blgrgbla ?!#
11: 53523905?!bla!-
13: BLA
14: B12la bLa
15: BLU bLA
-------------------------

*/