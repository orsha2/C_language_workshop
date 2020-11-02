#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_LEN 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "UI.h"

void test_driver();

int main()
{	
	test_driver();
	char* p_cmd_line[MAX_LINE_LEN+1];
	char* p_cmd;
	int arg1, arg2;
	
	Node* linked_list = NULL;
	do {
		scanf(" %[^\n]s", p_cmd_line);
	
		p_cmd = parser(p_cmd_line, &arg1, &arg2);
		
		linked_list = run(linked_list, p_cmd, arg1, arg2);
		
	} while (strcmp(p_cmd_line, "exit") != 0);
	
	return 0;
	
}