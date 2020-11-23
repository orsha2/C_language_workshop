#ifndef MY_GREP_H
#define MY_GREP_H 

#include "error_mgr.h"
#include "regex_handler.h"

void print_expression_and_flags(Regex_And_Flags* my_regex_and_flags, char* expression);
void print_regex(Regex_And_Flags* my_regex_and_flags);
Error_Code_t grep_execute_on_stream(FILE* input_stream, Regex_And_Flags* my_regex_and_flags); 


#endif 