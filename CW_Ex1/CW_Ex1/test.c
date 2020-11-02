//Authors:
//orsha    (orshahar1@mail.tau.ac.il)
//michaelz (zhitomirsky1@mail.tau.ac.il)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"


const char* RED = "\033[0;35m";
const char* YELLOW = "\033[01;33m";
const char* BLUE = "\033[1;34m";
const char* RESET = "\033[0m";
const char* BLOCK_TEST = "--------------------------------------------------";

void test(char** test, const int len_test, char* accpected_result, int test_number);

void test_driver() 
{
	
	int len_cmd ;
	int test_number;
	char* expected_result_test;

	// -------------TEST 1 -------------
	char* test_cmd_1[] = { "Add_starT -1\0","index -1\0","AdD_EnD -2\0","print \0","exit\0" };
	len_cmd = 5;
	test_number = 1;
	expected_result_test = "[-1, -2]";
	test(test_cmd_1, len_cmd, expected_result_test, test_number);

	// -------------TEST 2 -------------
	char* test_cmd_2[] = { "Add_starT 1\0","Add_starT 2\0","AdD_EnD 2\0","print \0","exit\0" };
	len_cmd = 5;
	test_number = 2;
	expected_result_test = "[2, 1, 2]";
	test(test_cmd_2, len_cmd, expected_result_test, test_number);

	// -------------TEST 3 -------------
	char* test_cmd_3[] = { "Add_end 1\0","Add_end 2\0","del 1\0","del 0\0","print \0","exit\0" };
	len_cmd = 6;
	test_number = 3;
	expected_result_test = "[]";
	test(test_cmd_3, len_cmd, expected_result_test, test_number);

	// -------------TEST 4 -------------
	char* test_cmd_4[] = { "Add_end 1\0","Add_end 2\0","add_after 3 2 \0","del 0\0","print \0","exit\0" };
	len_cmd = 6;
	test_number = 4;
	expected_result_test = "[2, 3]";
	test(test_cmd_4, len_cmd, expected_result_test, test_number);

	// -------------TEST 5 -------------
	char* test_cmd_5[] = { "Add_end 1\0","Add_end 2\0","index 1 \0","index 10\0","print \0","exit\0" };
	len_cmd = 6;
	test_number = 5;
	expected_result_test = "[1, 2]";
	test(test_cmd_5, len_cmd, expected_result_test, test_number);

	// -------------TEST 6 -------------
	char* test_cmd_6[] = { "Add_end 1\0","add_sTart 12\0","add_sTart 120\0", "add_sTart 125\0", "add_sTart 129\0", "index 1 \0","index 10\0","print \0", "del 4\0","print \0", "exit\0" };
	len_cmd = 10;
	test_number = 6;
	expected_result_test = "[129, 125, 120, 12]";
	test(test_cmd_6, len_cmd, expected_result_test, test_number);

	// -------------TEST 7 -------------
	char* test_cmd_7[] = { "print \0", "exit\0" };
	len_cmd = 2;
	test_number = 7;
	expected_result_test = "[]";
	test(test_cmd_7, len_cmd, expected_result_test, test_number);
}

void test(char** test, const int len_test, char* expected_result_test,int test_number)
{
	char* p_cmd = (char*)malloc(100 + 1);
	int arg1, arg2;
	printf("\n%stest (%d): %s\n", RED, test_number, RESET);
	Node* linked_list = NULL;
	for (int i = 0; i < len_test; i++) {
		strcpy(p_cmd, test[i]);
		printf("\t%s---%s---%s\n", YELLOW, p_cmd, RESET);

		parser(p_cmd, &arg1, &arg2);
		linked_list = run(linked_list, p_cmd, arg1, arg2);
		if (strcmp(p_cmd, "exit") == 0)
			break;

	}
	printf("%sexpected result test : %s%s\n", BLUE, expected_result_test, RESET);
	printf("%s\n", BLOCK_TEST);
	free(p_cmd);
}