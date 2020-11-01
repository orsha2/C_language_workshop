#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_LEN 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "UI.h"

int main()
{	
	char* p_cmd = (char*)malloc(MAX_LINE_LEN+1);
	int arg1, arg2;
	
	Node* linked_list = NULL;
	do {
		scanf(" %[^\n]s", p_cmd);
	
		parser(p_cmd, &arg1, &arg2);
		
		linked_list = run(linked_list, p_cmd, arg1, arg2);
		
	} while (strcmp(p_cmd, "exit") != 0);
	
	free(p_cmd);
	return 0;
	
}
