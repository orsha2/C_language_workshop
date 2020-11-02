#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "UI.h"

#define CMD_ARRAY_LEN 7
#define ONE_ARG_CMD_LEN 4
#define TWO_ARG_CMD_LEN 1

typedef enum { ADD_START,  ADD_END,  DEL,  INDEX,  ADD_AFTER , PRINT,  EXIT} command;
const char* CMD_ARRAY[] = { "add_start", "add_end", "del", "index", "add_after", "print", "exit" };
const char* ONE_ARG_CMD[] = { "add_start", "add_end", "del", "index"};
const char* TWO_ARG_CMD[] = { "add_after" };

char* to_lowercase(char* p_word);
char* my_strtok(char** p_line);
int get_cmd_index(const char* p_cmd);
int get_arg_from_line_and_advance_line(char** line);
bool is_member_cmd(char* p_cmd, const char* cmd_array[], const int array_len);


char* parser(char* p_cmd_line, int* p_arg1, int* p_arg2)
{
	char* p_cmd;
	char* rest_of_the_line = p_cmd_line;

	p_cmd = my_strtok(&rest_of_the_line);

	p_cmd = to_lowercase(p_cmd);

	bool is_one_arg_cmd = is_member_cmd(p_cmd, ONE_ARG_CMD, ONE_ARG_CMD_LEN);
	bool is_two_arg_cmd = is_member_cmd(p_cmd, TWO_ARG_CMD, TWO_ARG_CMD_LEN);

	if (is_one_arg_cmd || is_two_arg_cmd)
		*p_arg1 = get_arg_from_line_and_advance_line(&rest_of_the_line);

	if (is_two_arg_cmd)
		*p_arg2 = get_arg_from_line_and_advance_line(&rest_of_the_line);

	return p_cmd;
}	

int get_arg_from_line_and_advance_line(char** line)
{
	char* p_str_arg;

	p_str_arg = my_strtok(line);
	return atoi(p_str_arg);
	
}

char* to_lowercase(char* p_word)
{
	char* p_start = p_word;
	while (*p_word !='\0')
	{
		*p_word = tolower(*p_word);
		p_word++;
	}
	return p_start;
}

char* my_strtok(char** p_p_line) 
{
	char* p_line = *p_p_line;
	char* word_start = NULL; 
	word_start = p_line;

	while ((*p_line != ' ') && (*p_line != '\0'))
		p_line++;

	if (*p_line == '\0')
		return word_start;
	
	*p_line = '\0';
	 p_line++;
	*p_p_line = p_line; 

	return word_start;
}
 
bool is_member_cmd(char* p_cmd, const char* cmd_array[], const int array_len)
{
	int i = 0 ;
	for (i = 0; i < array_len; i++){
		if (strcmp(cmd_array[i], p_cmd) == 0)
			return true;
	}
	return false;
}

int get_cmd_index(const char* p_cmd)
{
	int i = 0; 
	for (i = 0; i < CMD_ARRAY_LEN; i++){
		if (strcmp(CMD_ARRAY[i], p_cmd) == 0)
			return i;
	}
	return -1;
}

Node* run(Node* list, const char* p_cmd, int arg1, int arg2)
{
	command cmd = get_cmd_index(p_cmd); 
	switch (cmd)
	{
	case ADD_START:
		list = add_to_start(list, arg1); break;
		
	case ADD_END:
		list = add_to_end(list, arg1); break;
		
	case DEL:
		list = del_node_at_index(list, arg1); break;
		
	case INDEX:
		printf("%d\n", get_index_via_data(list, arg1)); break;
	
	case ADD_AFTER:
		list = add_after(list, arg1, arg2); break;
		
	case PRINT:
		print_list(list); break;
		
	case EXIT:
		free_list(list); break;
		
	} 
	return list; 
}




