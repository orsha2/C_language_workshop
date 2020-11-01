#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"

#define CMD_ARRAY_LEN 7
#define ONE_ARG_CMD_LEN 5
#define TWO_ARG_CMD_LEN 1

typedef enum { cmd_add_start,  cmd_add_end,  cmd_del ,  cmd_index ,  cmd_add_after ,  cmd_print,  cmd_exit} commands;
const char* CMD_ARRAY[] = { "add_start", "add_end", "del" , "index" , "add_after" , "print", "exit" };
const char* ONE_ARG_CMD[] = { "add_start","add_end", "del","index","add_after" };
const char* TWO_ARG_CMD[] = { "add_after" };

char* to_lowercase(char* p_word);
char* my_strtok(char** p_line);
int is_member_cmd(char* p_cmd, const char* cmd_array[], const int array_len);

void parser(char* p_cmd, int* p_arg1, int* p_arg2)
{
	char* p_str_arg1;
	char* p_str_arg2;
	char* rest_of_the_line = p_cmd;

	p_cmd = my_strtok(&rest_of_the_line);

	p_cmd = to_lowercase(p_cmd);

	if (is_member_cmd(p_cmd ,ONE_ARG_CMD, ONE_ARG_CMD_LEN)) {
		p_str_arg1 = my_strtok(&rest_of_the_line);
		*p_arg1 = atoi(p_str_arg1);
	}

	if (is_member_cmd(p_cmd ,TWO_ARG_CMD, TWO_ARG_CMD_LEN)) {
		p_str_arg2 = my_strtok(&rest_of_the_line);
		*p_arg2 = atoi(p_str_arg2);
	}
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

char* my_strtok(char** p_p_line) {

	char* p_line = *p_p_line;
	char* start = NULL; 
	start = p_line;

	while ((*p_line != ' ') && (*p_line != '\0'))
		p_line++;

	if (*p_line == '\0')
		return start;
	
	*p_line = '\0';
	 p_line++;
	*p_p_line = p_line; 

	return start;
}
 
int is_member_cmd(char* p_cmd, const char* cmd_array[], const int array_len)
{
	int i = 0 ;
	for (i = 0; i < array_len; i++){
		if (strcmp(cmd_array[i], p_cmd) == 0)
			return 1;
	}
	return 0;
}

int get_cmd_index(char* p_cmd)
{
	int i =0 ; 
	for (i = 0; i < CMD_ARRAY_LEN; i++){
		if (strcmp(CMD_ARRAY[i], p_cmd) == 0)
			return i;
	}
	return -1;
}

Node* run(Node* list, char* p_cmd, int arg1, int arg2)
{
	commands command =get_cmd_index(p_cmd); 
	switch (command)
	{
	case cmd_add_start:
		list = add_to_start(list, arg1);
		break;
	case cmd_add_end:
		list = add_to_end(list, arg1);
		break;
	case cmd_del:
		list = del_node_at_index(list, arg1);
		break; 
	case cmd_index:
		printf("%d\n", get_index_via_data(list, arg1)); 
		break; 
	case cmd_add_after:
		list = add_after(list, arg1, arg2);
		break;
	case cmd_print:
		print_list(list);
		break;
	case cmd_exit:
		free_list(list);
		break;
	} 
	return list; 
}




